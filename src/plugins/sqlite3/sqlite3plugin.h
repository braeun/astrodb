#ifndef SQLITE3PLUGIN_H
#define SQLITE3PLUGIN_H

#include <astrodb/plugin.h>

namespace astrodb {

class Sqlite3Plugin: public Plugin
{
public:
  Sqlite3Plugin();
  ~Sqlite3Plugin();

  virtual std::string getName() const override;

  virtual std::string getVersion() const override;

  virtual std::vector<std::string> getDrivers() const override;

  virtual std::unique_ptr<Database> connect(const std::string& driver, const std::string& db, const std::string& user, const std::string& passwd) override;

};

DEFINE_PLUGIN(Sqlite3Plugin)

} // namespace astrodb


#endif // SQLITE3PLUGIN_H
