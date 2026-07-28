#include "sqlite3database.h"
#include "sqlite3cameratable.h"
#include "sqlite3objecttable.h"
#include "sqlite3observertable.h"
#include "sqlite3telescopetable.h"
#include <stdexcept>

namespace astrodb {

Sqlite3Database::Sqlite3Database(const std::string& filename)
{
  int ret = sqlite3_open(filename.c_str(),&db);
  if (ret != SQLITE_OK)
  {
    std::string err = sqlite3_errmsg(db);
    sqlite3_close(db);
    throw std::runtime_error(err);
  }
  cameraTable = std::make_unique<Sqlite3CameraTable>(db);
  objectTable = std::make_unique<Sqlite3ObjectTable>(db);
  observerTable = std::make_unique<Sqlite3ObserverTable>(db);
  telescopeTable = std::make_unique<Sqlite3TelescopeTable>(db);
}

Sqlite3Database::~Sqlite3Database()
{
  if (db)
  {
    sqlite3_close(db);
  }
}

CameraTable* Sqlite3Database::getCameraTable()
{
  return cameraTable.get();
}

ObjectTable* Sqlite3Database::getObjectTable()
{
  return objectTable.get();
}

ObserverTable* Sqlite3Database::getObserverTable()
{
  return observerTable.get();
}

TelescopeTable* Sqlite3Database::getTelescopeTable()
{
  return telescopeTable.get();
}

} // namespace astrodb
