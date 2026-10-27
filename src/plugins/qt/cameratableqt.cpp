#include "cameratableqt.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace astrodb {

CameraTableQt::CameraTableQt(const QString& con):
  con(con)
{
}

bool CameraTableQt::contains(const std::string& name)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("SELECT id FROM Cameras WHERE model=?");
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

std::vector<std::string> CameraTableQt::getNameList()
{
  std::vector<std::string> list;
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return list;
  QSqlQuery q(db);
  q.prepare("SELECT model FROM Cameras");
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

std::vector<Camera> CameraTableQt::getAll()
{
  std::vector<Camera> list;
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return list;
  QSqlQuery q(db);
  q.prepare("SELECT * FROM Cameras");
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

Camera CameraTableQt::get(const std::string& name)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return Camera();
  QSqlQuery q(db);
  q.prepare("SELECT * FROM Cameras where model=?");
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
  return Camera();
}

bool CameraTableQt::add(Camera c)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("INSERT INTO Cameras (model,width,height,pixelwidth,pixelheight,sensorwidth,sensorheight,bpp) VALUES (?,?,?,?,?,?,?,?)");
  q.bindValue(0,QString::fromStdString(c.getModel()));
  q.bindValue(1,c.getWidth());
  q.bindValue(2,c.getHeight());
  q.bindValue(3,c.getPixelWidth());
  q.bindValue(4,c.getPixelHeight());
  q.bindValue(5,c.getSensorWidth());
  q.bindValue(6,c.getSensorHeight());
  q.bindValue(7,c.getBpp());
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
  }
  return ret;
}

bool CameraTableQt::update(const Camera& c)
{
  if (c.getId() < 0) return add(c);
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("UPDATE Cameras SET model=?,width=?,height=?,pixelwidth=?,pixelheight=?,sensorwidth=?,sensorheight=?,bpp=? WHERE id=?");
  q.bindValue(0,QString::fromStdString(c.getModel()));
  q.bindValue(1,c.getWidth());
  q.bindValue(2,c.getHeight());
  q.bindValue(3,c.getPixelWidth());
  q.bindValue(4,c.getPixelHeight());
  q.bindValue(5,c.getSensorWidth());
  q.bindValue(6,c.getSensorHeight());
  q.bindValue(7,c.getBpp());
  q.bindValue(8,(qlonglong)c.getId());
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
  }
  return ret;
}

bool CameraTableQt::remove(const std::string& name)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("DELETE * FROM Cameras where model=?");
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

bool CameraTableQt::remove(int64_t id)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("DELETE * FROM Cameras where id=?");
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



Camera CameraTableQt::get(const QSqlQuery& q) const
{
  std::string model = q.value("model").toString().toStdString();
  int w = q.value("width").toInt();
  int h = q.value("height").toInt();
  Camera c(model,w,h);
  c.setId(q.value("id").toLongLong());
  c.setPixelWidth(q.value("pixelwidth").toDouble());
  c.setPixelHeight(q.value("pixelheight").toDouble());
  c.setSensorWidth(q.value("sensorwidth").toDouble());
  c.setSensorHeight(q.value("sensorheight").toDouble());
  c.setBpp(q.value("bpp").toInt());
  return c;
}

} // namespace astrodb
