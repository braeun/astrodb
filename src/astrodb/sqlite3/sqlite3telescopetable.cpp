#include "sqlite3telescopetable.h"
#include <cstring>
#include <iostream>

namespace astrodb {

Sqlite3TelescopeTable::Sqlite3TelescopeTable(sqlite3* db):
  db(db)
{
  assertTable();
}

Sqlite3TelescopeTable::~Sqlite3TelescopeTable()
{
}

bool Sqlite3TelescopeTable::contains(const std::string& id)
{
  std::string sqlQuery = "SELECT model FROM telescope WHERE model='"+id+"';";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_ROW;
}

std::vector<std::string> Sqlite3TelescopeTable::getIdList()
{
  std::string sqlQuery = "SELECT model FROM telescope;";
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

std::vector<Telescope> Sqlite3TelescopeTable::getAll()
{
  std::string sqlQuery = "SELECT model,f,d FROM telescope;";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  std::vector<Telescope> list;
  while ((ret = sqlite3_step(s)) == SQLITE_ROW)
  {
    std::string model = (const char*)sqlite3_column_text(s,0);
    double f = sqlite3_column_double(s,1);
    double d = sqlite3_column_double(s,2);
    Telescope t(model,f,d);
    list.push_back(t);
  }
  sqlite3_finalize(s);
  return list;
}

Telescope Sqlite3TelescopeTable::get(const std::string& id)
{
  std::string sqlQuery = "SELECT model,f,d FROM telescope WHERE model='"+id+"';";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  Telescope t;
  if ((ret = sqlite3_step(s)) == SQLITE_ROW)
  {
    std::string model = (const char*)sqlite3_column_text(s,0);
    double f = sqlite3_column_double(s,1);
    double d = sqlite3_column_double(s,2);
    t = Telescope(model,f,d);
  }
  sqlite3_finalize(s);
  return t;
}

bool Sqlite3TelescopeTable::add(const Telescope& t)
{
  std::string sql = "INSERT INTO telescope (model,f,d) VALUES (?,?,?);";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sql.c_str(),sql.length(),&s,nullptr);
  sqlite3_bind_text(s,1,t.getModel().c_str(),-1,SQLITE_STATIC);
  sqlite3_bind_double(s,2,t.getFocalLength());
  sqlite3_bind_double(s,3,t.getAperture());
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}

bool Sqlite3TelescopeTable::update(const Telescope& t)
{
  std::string sql = "UPDATE telescope SET f=?,d=? WHERE model='?';";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sql.c_str(),sql.length(),&s,nullptr);
  sqlite3_bind_double(s,1,t.getFocalLength());
  sqlite3_bind_double(s,2,t.getAperture());
  sqlite3_bind_text(s,3,t.getModel().c_str(),-1,SQLITE_STATIC);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}

bool Sqlite3TelescopeTable::remove(const std::string& id)
{
  std::string sqlQuery = "DELETE FROM telescope WHERE model='"+id+"';";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}



void Sqlite3TelescopeTable::assertTable()
{
  const char* sqlQuery = "SELECT name FROM sqlite_schema WHERE type='table' AND name='telescope';";
  const char* sqlCreate = "CREATE TABLE telescope("
                          "id INT PRIMARY KEY     NOT NULL, "
                          "model          TEXT    NOT NULL, "
                          "f     REAL, "
                          "d    REAL); ";
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
