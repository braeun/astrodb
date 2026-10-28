#include "databaseqt.h"
#include <astrodb/utils.h>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFileInfo>

namespace astrodb {

DatabaseQt::DatabaseQt(const std::string& driver, const std::string& dbname, const std::string& user, const std::string& passwd)
{
  std::string name = dbname;
  con = QDateTime::currentDateTimeUtc().toString(Qt::DateFormat::ISODateWithMs);
  if (QString::fromStdString(driver).toUpper() == "QSQLITE")
  {
    if (name.empty())
    {
      name = utils::getUserDataPath() + "/astrodb.sqlite";
    }
    setupSQLite(name,user,passwd);
  }
  if (name.empty())
  {
    name = "astrodb";
  }
  auto db = QSqlDatabase::addDatabase(QString::fromStdString(driver),con);
  db.setDatabaseName(QString::fromStdString(name));
  db.setUserName(QString::fromStdString(user));
  db.setPassword(QString::fromStdString(passwd));
  cameraTable = std::make_unique<CameraTableQt>(con);
  infoSnippetTable = std::make_unique<InfoSnippetTableQt>(con);
  objectTable = std::make_unique<ObjectTableQt>(con);
  observerTable = std::make_unique<ObserverTableQt>(con);
  telescopeTable = std::make_unique<TelescopeTableQt>(con);
}

void DatabaseQt::commit()
{
}

CameraTable* DatabaseQt::getCameraTable()
{
  return cameraTable.get();
}

InfoSnippetTable* DatabaseQt::getInfoSnippetTable()
{
  return infoSnippetTable.get();
}

ObjectTable* DatabaseQt::getObjectTable()
{
  return objectTable.get();
}

ObserverTable* DatabaseQt::getObserverTable()
{
  return observerTable.get();
}

TelescopeTable* DatabaseQt::getTelescopeTable()
{
  return telescopeTable.get();
}

const char* cmds[]{
  "CREATE TABLE Cameras (id SERIAL PRIMARY KEY,model VARCHAR(128) UNIQUE NOT NULL,width INTEGER,height INTEGER,pixelwidth REAL,pixelheight REAL,sensorwidth REAL,sensorheight REAL,bpp INTEGER);",
  "CREATE TABLE Objects (id SERIAL PRIMARY KEY,name VARCHAR(128) UNIQUE NOT NULL);",
  "CREATE TABLE Observers (id SERIAL PRIMARY KEY,name VARCHAR(128) UNIQUE NOT NULL);",
  "CREATE TABLE Telescopes (id SERIAL PRIMARY KEY,model VARCHAR(128) UNIQUE NOT NULL,focallength REAL,aperture REAL);",
  "CREATE TABLE InfoSnippets (id SERIAL PRIMARY KEY,key VARCHAR(128) UNIQUE NOT NULL,context VARCHAR(128) UNIQUE NOT NULL,note TEXT);"
};

void DatabaseQt::setupSQLite(const std::string& dbname, const std::string& user, const std::string& passwd)
{
  if (!QFileInfo::exists(QString::fromStdString(dbname)))
  {
    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QString::fromStdString(dbname));
    db.setUserName(QString::fromStdString(user));
    db.setPassword(QString::fromStdString(passwd));
    if (!(db.isValid() && db.isOpen())) throw std::runtime_error("Failed to open SQLITE database");
    {
      QSqlQuery q(db);
      q.prepare(cmds[0]);
      bool ret = q.exec();
      if (!ret) throw std::runtime_error(q.lastError().text().toStdString());
    }
    {
      QSqlQuery q(db);
      q.prepare(cmds[1]);
      bool ret = q.exec();
      if (!ret) throw std::runtime_error(q.lastError().text().toStdString());
    }
    {
      QSqlQuery q(db);
      q.prepare(cmds[2]);
      bool ret = q.exec();
      if (!ret) throw std::runtime_error(q.lastError().text().toStdString());
    }
    {
      QSqlQuery q(db);
      q.prepare(cmds[3]);
      bool ret = q.exec();
      if (!ret) throw std::runtime_error(q.lastError().text().toStdString());
    }
    {
      QSqlQuery q(db);
      q.prepare(cmds[4]);
      bool ret = q.exec();
      if (!ret) throw std::runtime_error(q.lastError().text().toStdString());
    }
  }
}



} // namespace astrodb
