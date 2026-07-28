#include "qtdatabase.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>

namespace astrodb {

QtDatabase::QtDatabase(const QString& host, const QString& user, const QString& password, const QString& driver, const QString& database)
{
  if (QSqlDatabase::contains(database))
  {
    QSqlDatabase::database(database,false).close();
    QSqlDatabase::removeDatabase(database);
  }
  QSqlDatabase db = QSqlDatabase::addDatabase(driver,database);
  db.setHostName(host);
  db.setDatabaseName(database);
  db.setUserName(user);
  db.setPassword(password);
  if (!db.open())
  {
    qWarning() << db.lastError().text();
  }
}

}
