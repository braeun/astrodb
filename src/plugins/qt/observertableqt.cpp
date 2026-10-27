#include "observertableqt.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


namespace astrodb {

ObserverTableQt::ObserverTableQt(const QString& con):
  con(con)
{
}

bool ObserverTableQt::contains(const std::string& name)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("SELECT id FROM Observers WHERE name=?");
  q.bindValue(0,QString::fromStdString(name));
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
    return false;
  }
  return q.next();
}

std::vector<std::string> ObserverTableQt::getNameList()
{
  std::vector<std::string> list;
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return list;
  QSqlQuery q(db);
  q.prepare("SELECT name FROM Observers");
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
  }
  else
  {
    while (q.next())
    {
      list.push_back(q.value(0).toString().toStdString());
    }
  }
  return list;
}

std::vector<Observer> ObserverTableQt::getAll()
{
  std::vector<Observer> list;
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return list;
  QSqlQuery q(db);
  q.prepare("SELECT * FROM Observers");
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
  }
  else
  {
    while (q.next())
    {
      list.push_back(get(q));
    }
  }
  return list;
}

Observer ObserverTableQt::get(const std::string& name)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return Observer();
  QSqlQuery q(db);
  q.prepare("SELECT * FROM Observers where name=?");
  q.bindValue(0,QString::fromStdString(name));
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
  }
  else
  {
    if (q.next())
    {
      return get(q);
    }
  }
  return Observer();
}

bool ObserverTableQt::add(Observer c)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("INSERT INTO Observers (name) VALUES (?)");
  q.bindValue(0,QString::fromStdString(c.getName()));
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
  }
  return ret;
}

bool ObserverTableQt::update(const Observer& c)
{
  if (c.getId() < 0) return add(c);
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("UPDATE Observers SET name=? WHERE id=?");
  q.bindValue(0,QString::fromStdString(c.getName()));
  q.bindValue(1,(qlonglong)c.getId());
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
  }
  return ret;
}

bool ObserverTableQt::remove(const std::string& name)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("DELETE * FROM Observers where name=?");
  q.bindValue(0,QString::fromStdString(name));
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
  }
  return ret;
}

bool ObserverTableQt::remove(int64_t id)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("DELETE * FROM Observers where id=?");
  q.bindValue(0,(qlonglong)id);
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
  }
  return ret;
}



Observer ObserverTableQt::get(const QSqlQuery& q) const
{
  std::string name = q.value("name").toString().toStdString();
  Observer o(name);
  o.setId(q.value("id").toLongLong());
  return o;
}



} // namespace astrodb
