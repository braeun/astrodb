#ifndef PLUGINQT6_H
#define PLUGINQT6_H

#include <astrodb/plugin.h>

namespace astrodb {

class PluginQt: public Plugin
{
public:
  PluginQt();
  ~PluginQt();

  virtual std::string getName() const override;

  virtual std::string getVersion() const override;

  virtual std::vector<std::string> getDrivers() const override;

  virtual std::unique_ptr<Database> connect(const std::string& driver, const std::string& db, const std::string& user, const std::string& passwd) override;

};

DEFINE_PLUGIN(PluginQt)

} // namespace astrodb

#endif // PLUGINQT6_H
