#include "sqlite3observertable.h"
#include <cstring>
#include <iostream>

namespace astrodb {

Sqlite3ObserverTable::Sqlite3ObserverTable(sqlite3* db):
  db(db)
{
  assertTable();
}

Sqlite3ObserverTable::~Sqlite3ObserverTable()
{
}

bool Sqlite3ObserverTable::contains(const std::string& id)
{
  std::string sqlQuery = "SELECT name FROM observer WHERE name='"+id+"';";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_ROW;
}

std::vector<std::string> Sqlite3ObserverTable::getIdList()
{
  std::string sqlQuery = "SELECT name FROM observer;";
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

std::vector<Observer> Sqlite3ObserverTable::getAll()
{
  std::string sqlQuery = "SELECT name FROM observer;";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  std::vector<Observer> list;
  while ((ret = sqlite3_step(s)) == SQLITE_ROW)
  {
    std::string name = (const char*)sqlite3_column_text(s,0);
    Observer o(name);
    list.push_back(o);
  }
  sqlite3_finalize(s);
  return list;
}

Observer Sqlite3ObserverTable::get(const std::string& id)
{
  std::string sqlQuery = "SELECT name FROM observer WHERE name='"+id+"';";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  Observer o;
  if ((ret = sqlite3_step(s)) == SQLITE_ROW)
  {
    std::string name = (const char*)sqlite3_column_text(s,0);
    o = Observer(name);
  }
  sqlite3_finalize(s);
  return o;
}

bool Sqlite3ObserverTable::add(const Observer& t)
{
  std::string sql = "INSERT INTO observer (name) VALUES (?);";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sql.c_str(),sql.length(),&s,nullptr);
  sqlite3_bind_text(s,1,t.getName().c_str(),-1,SQLITE_STATIC);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}

bool Sqlite3ObserverTable::update(const Observer& t)
{
  // std::string sql = "UPDATE observer SET f=?,d=? WHERE name='?';";
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

bool Sqlite3ObserverTable::remove(const std::string& id)
{
  std::string sqlQuery = "DELETE FROM observer WHERE name='"+id+"';";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}



void Sqlite3ObserverTable::assertTable()
{
  const char* sqlQuery = "SELECT name FROM sqlite_schema WHERE type='table' AND name='observer';";
  const char* sqlCreate = "CREATE TABLE observer("
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
