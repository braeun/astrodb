#include "databaseqt.h"
#include <QDateTime>
#include <QSqlDatabase>

namespace astrodb {

DatabaseQt::DatabaseQt(const std::string& driver, const std::string& dbname, const std::string& user, const std::string& passwd)
{
  con = QDateTime::currentDateTimeUtc().toString(Qt::DateFormat::ISODateWithMs);
  auto db = QSqlDatabase::addDatabase(QString::fromStdString(driver),con);
  db.setDatabaseName(QString::fromStdString(dbname));
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

} // namespace astrodb
