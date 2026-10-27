#ifndef PLUGIN_H
#define PLUGIN_H

#include "database.h"
#include <memory>
#include <string>
#include <vector>

namespace astrodb {

class Plugin {
public:
  Plugin();
  virtual ~Plugin();

  /**
     * @brief Get the name of the plugin.
     * @return the plugin name (defaults to 'undefined')
     */
  virtual std::string getName() const;

  /**
     * @brief Get the version of the plugin.
     * @return the plugin version (defaults to 'undefined')
     */
  virtual std::string getVersion() const;

  virtual std::vector<std::string> getDrivers() const;

  virtual std::unique_ptr<Database> connect(const std::string& driver, const std::string& db, const std::string& user, const std::string& passwd);

};


#define DEFINE_PLUGIN(classType)     \
extern "C" {                         \
Plugin* load()                       \
{                                    \
      return new classType();        \
}                                    \
                                     \
bool isAstroDBPlugin()               \
{                                    \
      return true;                   \
}                                    \
}

} // namespace astrodb

#endif // PLUGIN_H
