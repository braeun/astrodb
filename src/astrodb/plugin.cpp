#include "plugin.h"

namespace astrodb {

Plugin::Plugin()
{
}

Plugin::~Plugin()
{
}

std::string Plugin::getName() const
{
  return "undefined";
}

std::string Plugin::getVersion() const
{
  return "undefined";
}

std::vector<std::string> Plugin::getDrivers() const
{
  return {};
}

std::unique_ptr<Database> Plugin::connect(const std::string& driver, const std::string& db, const std::string& user, const std::string& passwd)
{
  return std::unique_ptr<Database>();
}

} // namespace astrodb
