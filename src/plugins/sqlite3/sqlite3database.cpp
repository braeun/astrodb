#include "sqlite3database.h"
#include "sqlite3cameratable.h"
#include "sqlite3infosnippettable.h"
#include "sqlite3objecttable.h"
#include "sqlite3observertable.h"
#include "sqlite3telescopetable.h"
#include <astrodb/utils.h>
#include <cstring>
#include <stdexcept>

namespace astrodb {

Sqlite3Database::Sqlite3Database(const std::string& fn):
  filename(fn)
{
  if (filename.empty())
  {
    filename = utils::getUserDataPath() + "/astrodb.sqlite";
  }
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
  infoSnippetTable = std::make_unique<Sqlite3InfoSnippetTable>(db);
}

Sqlite3Database::~Sqlite3Database()
{
  if (db)
  {
    sqlite3_close(db);
  }
}

std::string Sqlite3Database::getBackend() const
{
  return "Sqlite3 (native)";
}

std::string Sqlite3Database::getName() const
{
  return filename;
}

void Sqlite3Database::commit()
{
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

InfoSnippetTable* Sqlite3Database::getInfoSnippetTable()
{
  return infoSnippetTable.get();
}



static const char* cmds[]{
  "CREATE TABLE Cameras (id INTEGER PRIMARY KEY,model VARCHAR(128) UNIQUE NOT NULL,width INTEGER,height INTEGER,pixelwidth REAL,pixelheight REAL,sensorwidth REAL,sensorheight REAL,bpp INTEGER);",
  "CREATE TABLE Objects (id INTEGER PRIMARY KEY,name VARCHAR(128) UNIQUE NOT NULL);",
  "CREATE TABLE Observers (id INTEGER PRIMARY KEY,name VARCHAR(128) UNIQUE NOT NULL);",
  "CREATE TABLE Telescopes (id INTEGER PRIMARY KEY,model VARCHAR(128) UNIQUE NOT NULL,focallength REAL,aperture REAL);",
  "CREATE TABLE InfoSnippets (id INTEGER PRIMARY KEY,key VARCHAR(128) UNIQUE NOT NULL,context VARCHAR(128) UNIQUE NOT NULL,note TEXT);"
};

void Sqlite3Database::setupSQLite(const std::string& filename)
{
  sqlite3* db = nullptr;
  int ret = sqlite3_open(filename.c_str(),&db);
  if (ret != SQLITE_OK)
  {
    std::string err = sqlite3_errmsg(db);
    sqlite3_close(db);
    throw std::runtime_error(err);
  }
  {
    sqlite3_stmt* s;
    int ret = sqlite3_prepare_v2(db,cmds[0],strlen(cmds[0]),&s,nullptr);
    ret = sqlite3_step(s);
    sqlite3_finalize(s);
  }
  {
    sqlite3_stmt* s;
    int ret = sqlite3_prepare_v2(db,cmds[1],strlen(cmds[1]),&s,nullptr);
    ret = sqlite3_step(s);
    sqlite3_finalize(s);
  }
  {
    sqlite3_stmt* s;
    int ret = sqlite3_prepare_v2(db,cmds[2],strlen(cmds[2]),&s,nullptr);
    ret = sqlite3_step(s);
    sqlite3_finalize(s);
  }
  {
    sqlite3_stmt* s;
    int ret = sqlite3_prepare_v2(db,cmds[3],strlen(cmds[3]),&s,nullptr);
    ret = sqlite3_step(s);
    sqlite3_finalize(s);
  }
  {
    sqlite3_stmt* s;
    int ret = sqlite3_prepare_v2(db,cmds[4],strlen(cmds[4]),&s,nullptr);
    ret = sqlite3_step(s);
    sqlite3_finalize(s);
  }
  sqlite3_close(db);
}



} // namespace astrodb
