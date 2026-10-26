#include "database.h"
#include "memory/jsondatabase.h"
#include <algorithm>

namespace astrodb {

std::map<std::string,std::unique_ptr<Database>> Database::databases;

Database* Database::connect(const std::string& driver, const std::string& db, const std::string& user, const std::string& passwd, const std::string& con)
{
  auto it = databases.find(con);
  if (it != databases.end())
  {
    databases.erase(it);
  }
  std::unique_ptr<Database> p;
  std::string d = driver;
  std::transform(d.begin(),d.end(),d.begin(),::tolower);
  if (d == "json")
  {
    p.reset(new JsonDatabase(db));
  }
  if (p)
  {
    databases[con] = std::move(p);
  }
  return get(con);
}

Database* Database::get(const std::string& con)
{
  if (databases.find(con) != databases.end())
  {
    return databases.at(con).get();
  }
  return nullptr;
}




} // namespace astrodb
