#include "database.h"
#include "memory/jsondatabase.h"

namespace astrodb {

std::map<QString,std::unique_ptr<Database>> Database::databases;

Database* Database::connect(const QString& driver, const QString& db, const QString& user, const QString& passwd, const QString& con)
{
  auto it = databases.find(con);
  if (it != databases.end())
  {
    databases.erase(it);
  }
  std::unique_ptr<Database> p;
  if (driver.toLower() == "json")
  {
    p.reset(new JsonDatabase(db));
  }
  if (p)
  {
    databases[con] = std::move(p);
  }
  return get(con);
}

Database* Database::get(const QString& con)
{
  if (databases.find(con) != databases.end())
  {
    return databases.at(con).get();
  }
  return nullptr;
}




} // namespace astrodb
