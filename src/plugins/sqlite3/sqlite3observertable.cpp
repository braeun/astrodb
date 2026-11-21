#include "sqlite3observertable.h"
#include <chrono>
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
  std::string sqlQuery = "SELECT name FROM Observers WHERE name='"+id+"';";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_ROW;
}

std::vector<std::string> Sqlite3ObserverTable::getNameList()
{
  std::string sqlQuery = "SELECT name FROM Observers;";
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
  std::string sqlQuery = "SELECT id,name FROM Observers;";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  std::vector<Observer> list;
  while ((ret = sqlite3_step(s)) == SQLITE_ROW)
  {
    std::string name = (const char*)sqlite3_column_text(s,1);
    Observer o(name);
    o.setId(sqlite3_column_int(s,0));
    list.push_back(o);
  }
  sqlite3_finalize(s);
  return list;
}

Observer Sqlite3ObserverTable::get(const std::string& id)
{
  std::string sqlQuery = "SELECT id,name FROM Observers WHERE name='"+id+"';";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  Observer o;
  if ((ret = sqlite3_step(s)) == SQLITE_ROW)
  {
    std::string name = (const char*)sqlite3_column_text(s,1);
    o = Observer(name);
    o.setId(sqlite3_column_int(s,0));
  }
  sqlite3_finalize(s);
  return o;
}

bool Sqlite3ObserverTable::add(Observer o)
{
  if (o.getName().empty())
  {
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    o.setName("Observer "+std::to_string(ms));
  }
  std::string sql = "INSERT INTO Observers (name) VALUES (?);";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sql.c_str(),sql.length(),&s,nullptr);
  sqlite3_bind_text(s,1,o.getName().c_str(),-1,SQLITE_STATIC);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}

bool Sqlite3ObserverTable::update(const Observer& t)
{
  std::string sql = "UPDATE Observers SET name=? WHERE id=?;";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sql.c_str(),sql.length(),&s,nullptr);
  sqlite3_bind_text(s,1,t.getName().c_str(),-1,SQLITE_STATIC);
  sqlite3_bind_int(s,2,t.getId());
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}

bool Sqlite3ObserverTable::remove(const std::string& id)
{
  std::string sqlQuery = "DELETE FROM Observers WHERE name='"+id+"';";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}

bool Sqlite3ObserverTable::remove(int64_t id)
{
  std::string sqlQuery = "DELETE FROM Observers WHERE id=?;";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  sqlite3_bind_int(s,1,id);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}



void Sqlite3ObserverTable::assertTable()
{
  const char* sqlQuery = "SELECT name FROM sqlite_schema WHERE type='table' AND name='Observers';";
  const char* sqlCreate = "CREATE TABLE Observers("
                          "id INTEGER PRIMARY KEY, "
                          "name TEXT NOT NULL);";
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
