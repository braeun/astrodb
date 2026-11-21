#include "sqlite3plugin.h"
#include "sqlite3database.h"
#include <sstream>

namespace astrodb {

Sqlite3Plugin::Sqlite3Plugin()
{
}

Sqlite3Plugin::~Sqlite3Plugin()
{
}

std::string Sqlite3Plugin::getName() const
{
  return "Native Sqlite3 Plugin";
}

std::string Sqlite3Plugin::getVersion() const
{
  std::ostringstream s;
  s << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH;
  return s.str();
  return "undefined";
}

std::vector<std::string> Sqlite3Plugin::getDrivers() const
{
  std::vector<std::string> list;
  list.push_back("Sqlite3 (native)");
  return list;
}

std::unique_ptr<Database> Sqlite3Plugin::connect(const std::string& driver, const std::string& db, const std::string& user, const std::string& passwd)
{
  return std::make_unique<Sqlite3Database>(db);
}

} // namespace astrodb

