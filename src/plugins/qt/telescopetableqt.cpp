#include "telescopetableqt.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace astrodb {

TelescopeTableQt::TelescopeTableQt(const QString& con):
  con(con)
{
}

bool TelescopeTableQt::contains(const std::string& name)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("SELECT id FROM Telescopes WHERE model=?");
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

std::vector<std::string> TelescopeTableQt::getNameList()
{
  std::vector<std::string> list;
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return list;
  QSqlQuery q(db);
  q.prepare("SELECT model FROM Telescopes");
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

std::vector<Telescope> TelescopeTableQt::getAll()
{
  std::vector<Telescope> list;
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return list;
  QSqlQuery q(db);
  q.prepare("SELECT * FROM Telescopes");
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

Telescope TelescopeTableQt::get(const std::string& name)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return Telescope();
  QSqlQuery q(db);
  q.prepare("SELECT * FROM Telescopes where model=?");
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
  return Telescope();
}

bool TelescopeTableQt::add(Telescope c)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("INSERT INTO Telescopes (model,focallength,aperture) VALUES (?,?,?)");
  q.bindValue(0,QString::fromStdString(c.getModel()));
  q.bindValue(1,c.getFocalLength());
  q.bindValue(2,c.getAperture());
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
  }
  return ret;
}

bool TelescopeTableQt::update(const Telescope& c)
{
  if (c.getId() < 0) return add(c);
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("UPDATE Telescopes SET model=?,focallength=?,aperture=? WHERE id=?");
  q.bindValue(0,QString::fromStdString(c.getModel()));
  q.bindValue(1,c.getFocalLength());
  q.bindValue(2,c.getAperture());
  q.bindValue(3,(qlonglong)c.getId());
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
  }
  return ret;
}

bool TelescopeTableQt::remove(const std::string& name)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("DELETE * FROM Telescopes where model=?");
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

bool TelescopeTableQt::remove(int64_t id)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("DELETE * FROM Telescopes where id=?");
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



Telescope TelescopeTableQt::get(const QSqlQuery& q) const
{
  std::string model = q.value("model").toString().toStdString();
  double f = q.value("focallength").toDouble();
  double d = q.value("aperture").toDouble();
  Telescope o(model,f,d);
  o.setId(q.value("id").toLongLong());
  return o;
}


} // namespace astrodb
