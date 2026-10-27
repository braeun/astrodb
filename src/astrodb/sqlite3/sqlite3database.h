#ifndef ASTRODB_SQLITE3DATABASE_H
#define ASTRODB_SQLITE3DATABASE_H

#include "../database.h"
#include <sqlite3.h>
#include <memory>
#include <string>

namespace astrodb {

class CameraTable;
class Sqlite3CameraTable;
class Sqlite3ObjectTable;
class Sqlite3ObserverTable;
class Sqlite3TelescopeTable;
class ObjectTable;
class ObserverTable;
class TelescopeTable;

class Sqlite3Database: public Database
{
public:
  Sqlite3Database(const std::string& filename);
  ~Sqlite3Database();

  virtual CameraTable* getCameraTable() override;

  virtual ObjectTable* getObjectTable() override;

  virtual ObserverTable* getObserverTable() override;

  virtual TelescopeTable* getTelescopeTable() override;

private:
  sqlite3* db;
  std::unique_ptr<Sqlite3CameraTable> cameraTable;
  std::unique_ptr<Sqlite3ObjectTable> objectTable;
  std::unique_ptr<Sqlite3ObserverTable> observerTable;
  std::unique_ptr<Sqlite3TelescopeTable> telescopeTable;
};

} // namespace astrodb

#endif // SQLITE3DATABASE_H
