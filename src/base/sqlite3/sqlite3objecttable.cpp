#include "sqlite3objecttable.h"
#include <cstring>
#include <iostream>

namespace astrodb {

Sqlite3ObjectTable::Sqlite3ObjectTable(sqlite3* db):
  db(db)
{
  assertTable();
}

Sqlite3ObjectTable::~Sqlite3ObjectTable()
{
}

bool Sqlite3ObjectTable::contains(const std::string& id)
{
  std::string sqlQuery = "SELECT name FROM object WHERE name='"+id+"';";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_ROW;
}

std::vector<std::string> Sqlite3ObjectTable::getIdList()
{
  std::string sqlQuery = "SELECT name FROM object;";
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

std::vector<Object> Sqlite3ObjectTable::getAll()
{
  std::string sqlQuery = "SELECT name FROM object;";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  std::vector<Object> list;
  while ((ret = sqlite3_step(s)) == SQLITE_ROW)
  {
    std::string name = (const char*)sqlite3_column_text(s,0);
    Object o(name);
    list.push_back(o);
  }
  sqlite3_finalize(s);
  return list;
}

Object Sqlite3ObjectTable::get(const std::string& id)
{
  std::string sqlQuery = "SELECT name FROM object WHERE name='"+id+"';";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  Object o;
  if ((ret = sqlite3_step(s)) == SQLITE_ROW)
  {
    std::string name = (const char*)sqlite3_column_text(s,0);
    o = Object(name);
  }
  sqlite3_finalize(s);
  return o;
}

bool Sqlite3ObjectTable::add(const Object& t)
{
  std::string sql = "INSERT INTO object (name) VALUES (?);";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sql.c_str(),sql.length(),&s,nullptr);
  sqlite3_bind_text(s,1,t.getName().c_str(),-1,SQLITE_STATIC);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}

bool Sqlite3ObjectTable::update(const Object& t)
{
  // std::string sql = "UPDATE object SET f=?,d=? WHERE name='?';";
  // sqlite3_stmt* s;
  // int ret = sqlite3_prepare_v2(db,sql.c_str(),sql.length(),&s,nullptr);
  // sqlite3_bind_double(s,1,t.getFocalLength());
  // sqlite3_bind_double(s,2,t.getAperture());
  // sqlite3_bind_text(s,3,t.getName().c_str(),-1,SQLITE_STATIC);
  // ret = sqlite3_step(s);
  // sqlite3_finalize(s);
  // return ret == SQLITE_DONE;
  return true;
}

bool Sqlite3ObjectTable::remove(const std::string& id)
{
  std::string sqlQuery = "DELETE FROM object WHERE name='"+id+"';";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}



void Sqlite3ObjectTable::assertTable()
{
  const char* sqlQuery = "SELECT name FROM sqlite_schema WHERE type='table' AND name='object';";
  const char* sqlCreate = "CREATE TABLE object("
                          "id INT PRIMARY KEY     NOT NULL, "
                          "name          TEXT    NOT NULL);";
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

