#include "qtcameratable.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace astrodb {

QtCameraTable::QtCameraTable(const QString& db):
  db(db)
{
}

QtCameraTable::~QtCameraTable()
{
}

bool QtCameraTable::contains(const std::string& id)
{
  QSqlDatabase db = QSqlDatabase::database("IFDB",false);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("SELECT model FROM camera WHERE model=?");
  q.bindValue(0,QString::fromStdString(id));
  if (!q.exec())
  {
    qWarning() << q.lastError().text();
    return false;
  }
  return q.next();
}

std::vector<std::string> QtCameraTable::getIdList()
{
  std::vector<std::string> keys;
  QSqlDatabase db = QSqlDatabase::database("IFDB",false);
  if (!(db.isValid() && db.isOpen())) return keys;
  QSqlQuery q(db);
  q.prepare("SELECT model FROM camera");
  if (!q.exec())
  {
    qWarning() << q.lastError().text();
    return keys;
  }
  while (q.next())
  {
    keys.push_back(q.value(0).toString().toStdString());
  }
  return keys;
}

std::vector<Camera> QtCameraTable::getAll()
{
  std::vector<Camera> list;
  QSqlDatabase db = QSqlDatabase::database("IFDB",false);
  if (!(db.isValid() && db.isOpen())) return list;
  QSqlQuery q(db);
  q.prepare("SELECT model,width,height,pixelwidth,pixelheight,sensorwidth,sensorheight,bpp FROM camera");
  if (!q.exec())
  {
    qWarning() << q.lastError().text();
    return list;
  }
  while (q.next())
  {
    std::string model = q.value(0).toString().toStdString();
    int w = q.value(1).toInt();
    int h = q.value(2).toInt();
    Camera c(model,w,h);
    c.setPixelWidth(q.value(3).toDouble());
    c.setPixelHeight(q.value(4).toDouble());
    c.setSensorWidth(q.value(5).toDouble());
    c.setSensorHeight(q.value(6).toDouble());
    c.setBpp(q.value(7).toInt());
    list.push_back(c);
  }
  return list;
}

Camera QtCameraTable::get(const std::string& id)
{
  Camera c;
  QSqlDatabase db = QSqlDatabase::database("IFDB",false);
  if (!(db.isValid() && db.isOpen())) return c;
  QSqlQuery q(db);
  q.prepare("SELECT model,width,height,pixelwidth,pixelheight,sensorwidth,sensorheight,bpp FROM camera WHERE model = ?");
  q.bindValue(0,QString::fromStdString(id));
  if (!q.exec())
  {
    qWarning() << q.lastError().text();
    return c;
  }
  if (q.next())
  {
    std::string model = q.value(0).toString().toStdString();
    int w = q.value(1).toInt();
    int h = q.value(2).toInt();
    c = Camera(model,w,h);
    c.setPixelWidth(q.value(3).toDouble());
    c.setPixelHeight(q.value(4).toDouble());
    c.setSensorWidth(q.value(5).toDouble());
    c.setSensorHeight(q.value(6).toDouble());
    c.setBpp(q.value(7).toInt());
  }
  return c;
}

bool QtCameraTable::add(const Camera& c)
{
  QSqlDatabase db = QSqlDatabase::database("IFDB",false);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("INSERT INTO camera (model,width,height,pixelwidth,pixelheight,sensorwidth,sensorheight,bpp) VALUES (?,?,?,?,?,?,?,?)");
  q.bindValue(0,QString::fromStdString(c.getModel()));
  q.bindValue(1,c.getWidth());
  q.bindValue(2,c.getHeight());
  q.bindValue(3,c.getPixelWidth());
  q.bindValue(4,c.getPixelHeight());
  q.bindValue(5,c.getSensorWidth());
  q.bindValue(6,c.getSensorHeight());
  q.bindValue(7,c.getBpp());
  if (!q.exec())
  {
    qWarning() << q.lastError().text();
    return false;
  }
  return true;
}

bool QtCameraTable::update(const Camera& c)
{
  QSqlDatabase db = QSqlDatabase::database("IFDB",false);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("UPDATE camera SET width=?,height=?,pixelwidth=?,pixelheight=?,sensorwidth=?,sensorheight=?,bpp=? WHERE model='?'");
  q.bindValue(0,c.getWidth());
  q.bindValue(1,c.getHeight());
  q.bindValue(2,c.getPixelWidth());
  q.bindValue(3,c.getPixelHeight());
  q.bindValue(4,c.getSensorWidth());
  q.bindValue(5,c.getSensorHeight());
  q.bindValue(6,c.getBpp());
  q.bindValue(7,QString::fromStdString(c.getModel()));
  if (!q.exec())
  {
    qWarning() << q.lastError().text();
    return false;
  }
  return true;
}

bool QtCameraTable::remove(const std::string& id)
{
  QSqlDatabase db = QSqlDatabase::database("IFDB",false);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("DELETE FROM camera WHERE model=?");
  q.bindValue(0,QString::fromStdString(id));
  if (!q.exec())
  {
    qWarning() << q.lastError().text();
    return false;
  }
  return true;
}



void QtCameraTable::assertTable()
{
  const char* sqlCreate = "CREATE TABLE camera("
                          "id INT PRIMARY KEY     NOT NULL, "
                          "model          TEXT    NOT NULL, "
                          "width          INT, "
                          "height         INT, "
                          "pixelwidth     REAL, "
                          "pixelheight    REAL, "
                          "sensorwidth    REAL, "
                          "sensorheight   REAL, "
                          "bpp            INT);";
  QSqlDatabase db = QSqlDatabase::database("IFDB",false);
  if (!(db.isValid() && db.isOpen()))
  {
    return;
  }
  QStringList tables = db.tables();
  if (!tables.contains("camera"))
  {
    QSqlQuery q(db);
    q.prepare(sqlCreate);
    if (!q.exec())
    {
      qWarning() << q.lastError().text();
    }
  }
}

} // namespace astrodb
