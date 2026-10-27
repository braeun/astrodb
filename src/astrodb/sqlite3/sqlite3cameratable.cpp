#include "sqlite3cameratable.h"
#include <cstring>
#include <iostream>

namespace astrodb {

Sqlite3CameraTable::Sqlite3CameraTable(sqlite3* db):
  db(db)
{
  assertTable();
}

Sqlite3CameraTable::~Sqlite3CameraTable()
{
}

bool Sqlite3CameraTable::contains(const std::string& id)
{
  std::string sqlQuery = "SELECT model FROM camera WHERE model='"+id+"';";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_ROW;
}

std::vector<std::string> Sqlite3CameraTable::getIdList()
{
  std::string sqlQuery = "SELECT model FROM camera;";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  std::vector<std::string> keys;
  while ((ret = sqlite3_step(s)) == SQLITE_ROW)
  {
    keys.push_back((const char*)sqlite3_column_text(s,0));
  }
  sqlite3_finalize(s);
  return keys;
}

std::vector<Camera> Sqlite3CameraTable::getAll()
{
  std::string sqlQuery = "SELECT model,width,height,pixelwidth,pixelheight,sensorwidth,sensorheight,bpp FROM camera;";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  std::vector<Camera> cameras;
  while ((ret = sqlite3_step(s)) == SQLITE_ROW)
  {
    std::string model = (const char*)sqlite3_column_text(s,0);
    int w = sqlite3_column_int(s,1);
    int h = sqlite3_column_int(s,2);
    Camera c(model,w,h);
    c.setPixelWidth(sqlite3_column_double(s,3));
    c.setPixelHeight(sqlite3_column_double(s,4));
    c.setSensorWidth(sqlite3_column_double(s,5));
    c.setSensorHeight(sqlite3_column_double(s,6));
    c.setBpp(sqlite3_column_int(s,7));
    cameras.push_back(c);
  }
  sqlite3_finalize(s);
  return cameras;
}

Camera Sqlite3CameraTable::get(const std::string& id)
{
  std::string sqlQuery = "SELECT model,width,height,pixelwidth,pixelheight,sensorwidth,sensorheight,bpp "
                         "FROM camera WHERE model='"+id+"';";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  Camera c;
  if ((ret = sqlite3_step(s)) == SQLITE_ROW)
  {
    std::string model = (const char*)sqlite3_column_text(s,0);
    int w = sqlite3_column_int(s,1);
    int h = sqlite3_column_int(s,2);
    c = Camera(model,w,h);
    c.setPixelWidth(sqlite3_column_double(s,3));
    c.setPixelHeight(sqlite3_column_double(s,4));
    c.setSensorWidth(sqlite3_column_double(s,5));
    c.setSensorHeight(sqlite3_column_double(s,6));
    c.setBpp(sqlite3_column_int(s,7));
  }
  sqlite3_finalize(s);
  return c;
}

bool Sqlite3CameraTable::add(const Camera& c)
{
  std::string sql = "INSERT INTO camera (model,width,height,pixelwidth,pixelheight,sensorwidth,sensorheight,bpp)"
                    " VALUES (?,?,?,?,?,?,?,?);";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sql.c_str(),sql.length(),&s,nullptr);
  sqlite3_bind_text(s,1,c.getModel().c_str(),-1,SQLITE_STATIC);
  sqlite3_bind_int(s,2,c.getWidth());
  sqlite3_bind_int(s,3,c.getHeight());
  sqlite3_bind_double(s,4,c.getPixelWidth());
  sqlite3_bind_double(s,5,c.getPixelHeight());
  sqlite3_bind_double(s,6,c.getSensorWidth());
  sqlite3_bind_double(s,7,c.getSensorHeight());
  sqlite3_bind_int(s,8,c.getBpp());
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}

bool Sqlite3CameraTable::update(const Camera& c)
{
  std::string sql = "UPDATE camera SET width=?,height=?,pixelwidth=?,pixelheight=?,sensorwidth=?,sensorheight=?,bpp=?"
                    " WHERE model='?';";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sql.c_str(),sql.length(),&s,nullptr);
  sqlite3_bind_int(s,1,c.getWidth());
  sqlite3_bind_int(s,2,c.getHeight());
  sqlite3_bind_double(s,3,c.getPixelWidth());
  sqlite3_bind_double(s,4,c.getPixelHeight());
  sqlite3_bind_double(s,5,c.getSensorWidth());
  sqlite3_bind_double(s,6,c.getSensorHeight());
  sqlite3_bind_int(s,7,c.getBpp());
  sqlite3_bind_text(s,8,c.getModel().c_str(),-1,SQLITE_STATIC);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}

bool Sqlite3CameraTable::remove(const std::string& id)
{
  std::string sqlQuery = "DELETE FROM camera WHERE model='"+id+"';";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}



void Sqlite3CameraTable::assertTable()
{
  const char* sqlQuery = "SELECT name FROM sqlite_schema WHERE type='table' AND name='camera';";
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
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery,std::strlen(sqlQuery),&s,nullptr);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  if (ret == SQLITE_DONE)
  {
    char* messaggeError;
    ret = sqlite3_exec(db, sqlCreate, nullptr, 0, &messaggeError);
    if (ret != SQLITE_OK)
    {
      std::cerr << "Error create table " << messaggeError << std::endl;
      sqlite3_free(messaggeError);
    }
    else
      std::cout << "Table created successfully" << std::endl;
  }
  else
  {
    std::cout << "Table exists" << std::endl;
  }
}

} // namespace astrodb
