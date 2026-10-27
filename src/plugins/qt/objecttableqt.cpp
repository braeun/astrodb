#include "objecttableqt.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace astrodb {

ObjectTableQt::ObjectTableQt(const QString& con):
  con(con)
{
}

bool ObjectTableQt::contains(const std::string& name)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("SELECT id FROM Objects WHERE name=?");
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

std::vector<std::string> ObjectTableQt::getNameList()
{
  std::vector<std::string> list;
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return list;
  QSqlQuery q(db);
  q.prepare("SELECT name FROM Objects");
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

std::vector<Object> ObjectTableQt::getAll()
{
  std::vector<Object> list;
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return list;
  QSqlQuery q(db);
  q.prepare("SELECT * FROM Objects");
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

Object ObjectTableQt::get(const std::string& name)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return Object();
  QSqlQuery q(db);
  q.prepare("SELECT * FROM Objects where name=?");
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
  return Object();
}

bool ObjectTableQt::add(Object c)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("INSERT INTO Objects (name) VALUES (?)");
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

bool ObjectTableQt::update(const Object& c)
{
  if (c.getId() < 0) return add(c);
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("UPDATE Objects SET name=? WHERE id=?");
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

bool ObjectTableQt::remove(const std::string& name)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("DELETE * FROM Objects where name=?");
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

bool ObjectTableQt::remove(int64_t id)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("DELETE * FROM Objects where id=?");
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



Object ObjectTableQt::get(const QSqlQuery& q) const
{
  std::string name = q.value("name").toString().toStdString();
  Object o(name);
  o.setId(q.value("id").toLongLong());
  return o;
}



} // namespace astrodb
