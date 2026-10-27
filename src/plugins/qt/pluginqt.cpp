#include "pluginqt.h"
#include "databaseqt.h"
#include <QSqlDatabase>
#include <sstream>

namespace astrodb {

PluginQt::PluginQt()
{
}

PluginQt::~PluginQt()
{
}

std::string PluginQt::getName() const
{
  return "Qt SqlDatabase Plugin";
}

std::string PluginQt::getVersion() const
{
  std::ostringstream s;
  s << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH;
  return s.str();
  return "undefined";
}

std::vector<std::string> PluginQt::getDrivers() const
{
  std::vector<std::string> list;
  for (const QString& driver : QSqlDatabase::drivers())
  {
    list.push_back(driver.toStdString());
  }
  return list;
}

std::unique_ptr<Database> PluginQt::connect(const std::string& driver, const std::string& db, const std::string& user, const std::string& passwd)
{
  return std::make_unique<DatabaseQt>(driver,db,user,passwd);
}

} // namespace astrodb
