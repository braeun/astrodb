#include "sqlite3objecttable.h"
#include <chrono>
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
  std::string sqlQuery = "SELECT name FROM Objects WHERE name='"+id+"';";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_ROW;
}

std::vector<std::string> Sqlite3ObjectTable::getNameList()
{
  std::string sqlQuery = "SELECT name FROM Objects;";
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
  std::string sqlQuery = "SELECT id,name FROM Objects;";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  std::vector<Object> list;
  while ((ret = sqlite3_step(s)) == SQLITE_ROW)
  {
    std::string name = (const char*)sqlite3_column_text(s,1);
    Object o(name);
    o.setId(sqlite3_column_int(s,0));
    list.push_back(o);
  }
  sqlite3_finalize(s);
  return list;
}

Object Sqlite3ObjectTable::get(const std::string& id)
{
  std::string sqlQuery = "SELECT id,name FROM Objects WHERE name=?;";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  sqlite3_bind_text(s,1,id.c_str(),-1,SQLITE_STATIC);
  Object o;
  if ((ret = sqlite3_step(s)) == SQLITE_ROW)
  {
    std::string name = (const char*)sqlite3_column_text(s,1);
    o = Object(name);
    o.setId(sqlite3_column_int(s,0));
  }
  sqlite3_finalize(s);
  return o;
}

bool Sqlite3ObjectTable::add(Object o)
{
  if (o.getName().empty())
  {
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    o.setName("Object "+std::to_string(ms));
  }
  std::string sql = "INSERT INTO Objects (name) VALUES (?);";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sql.c_str(),sql.length(),&s,nullptr);
  sqlite3_bind_text(s,1,o.getName().c_str(),-1,SQLITE_STATIC);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}

bool Sqlite3ObjectTable::update(const Object& t)
{
  std::string sql = "UPDATE Objects SET name=? WHERE id=?;";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sql.c_str(),sql.length(),&s,nullptr);
  sqlite3_bind_text(s,1,t.getName().c_str(),-1,SQLITE_STATIC);
  sqlite3_bind_int(s,2,t.getId());
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}

bool Sqlite3ObjectTable::remove(const std::string& id)
{
  std::string sqlQuery = "DELETE FROM Objects WHERE name=?;";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  sqlite3_bind_text(s,1,id.c_str(),-1,SQLITE_STATIC);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}

bool Sqlite3ObjectTable::remove(int64_t id)
{
  std::string sqlQuery = "DELETE FROM Objects WHERE id=?;";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  sqlite3_bind_int(s,1,id);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}



void Sqlite3ObjectTable::assertTable()
{
  const char* sqlQuery = "SELECT name FROM sqlite_schema WHERE type='table' AND name='Objects';";
  const char* sqlCreate = "CREATE TABLE Objects("
                          "id INTEGER PRIMARY KEY, "
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

