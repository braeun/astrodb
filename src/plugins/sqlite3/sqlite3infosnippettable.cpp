#include "sqlite3infosnippettable.h"
#include <cstring>
#include <iostream>

namespace astrodb {

Sqlite3InfoSnippetTable::Sqlite3InfoSnippetTable(sqlite3* db):
  db(db)
{
  assertTable();
}

Sqlite3InfoSnippetTable::~Sqlite3InfoSnippetTable()
{
}

std::set<std::string> Sqlite3InfoSnippetTable::getKeys()
{
  std::string sqlQuery = "SELECT UNIQUE(key) FROM InfoSnippets;";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  std::set<std::string> keys;
  while ((ret = sqlite3_step(s)) == SQLITE_ROW)
  {
    keys.insert((const char*)sqlite3_column_text(s,0));
  }
  sqlite3_finalize(s);
  return keys;
}

std::set<std::string> Sqlite3InfoSnippetTable::getKeys(const std::string& context)
{
  std::string sqlQuery = "SELECT UNIQUE(key) FROM InfoSnippets WHERE context=?;";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  sqlite3_bind_text(s,1,context.c_str(),-1,SQLITE_STATIC);
  std::set<std::string> keys;
  while ((ret = sqlite3_step(s)) == SQLITE_ROW)
  {
    keys.insert((const char*)sqlite3_column_text(s,0));
  }
  sqlite3_finalize(s);
  return keys;
}

std::set<std::string> Sqlite3InfoSnippetTable::getContexts()
{
  std::string sqlQuery = "SELECT UNIQUE(contexts) FROM InfoSnippets;";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  std::set<std::string> contexts;
  while ((ret = sqlite3_step(s)) == SQLITE_ROW)
  {
    contexts.insert((const char*)sqlite3_column_text(s,0));
  }
  sqlite3_finalize(s);
  return contexts;
}

std::set<std::string> Sqlite3InfoSnippetTable::getContexts(const std::string& key)
{
  std::string sqlQuery = "SELECT UNIQUE(contexts) FROM InfoSnippets WHERE key=?;";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  sqlite3_bind_text(s,1,key.c_str(),-1,SQLITE_STATIC);
  std::set<std::string> contexts;
  while ((ret = sqlite3_step(s)) == SQLITE_ROW)
  {
    contexts.insert((const char*)sqlite3_column_text(s,0));
  }
  sqlite3_finalize(s);
  return contexts;
}

std::vector<InfoSnippet> Sqlite3InfoSnippetTable::getSnippets(const std::string& key, const std::string& context)
{
  std::vector<InfoSnippet> list;
  sqlite3_stmt* s;
  int ret;
  if (key.empty() && context.empty())
  {
    std::string sqlQuery = "SELECT id,key,context,text FROM InfoSnippets;";
    ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  }
  else if (context.empty())
  {
    std::string sqlQuery = "SELECT id,key,context,text FROM InfoSnippets WHERE key=?;";
    ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
    sqlite3_bind_text(s,1,key.c_str(),-1,SQLITE_STATIC);
  }
  else if (key.empty())
  {
    std::string sqlQuery = "SELECT id,key,context,text FROM InfoSnippets WHERE context=?;";
    ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
    sqlite3_bind_text(s,1,context.c_str(),-1,SQLITE_STATIC);
  }
  else
  {
    std::string sqlQuery = "SELECT id,key,context,text FROM InfoSnippets WHERE key=? AND context=?;";
    ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
    sqlite3_bind_text(s,1,key.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_text(s,2,context.c_str(),-1,SQLITE_STATIC);
  }
  while ((ret = sqlite3_step(s)) == SQLITE_ROW)
  {
    int64_t id = sqlite3_column_int(s,0);
    std::string key = (const char*)sqlite3_column_text(s,1);
    std::string context = (const char*)sqlite3_column_text(s,2);
    std::string text = (const char*)sqlite3_column_text(s,3);
    InfoSnippet o(key,context,text);
    o.setId(id);
    list.push_back(o);
  }
  sqlite3_finalize(s);
  return list;
}

bool Sqlite3InfoSnippetTable::add(const InfoSnippet& c)
{
  std::string sqlQuery = "INSERT INTO InfoSnippets (key,context,note) VALUES (?,?,?);";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  sqlite3_bind_text(s,1,c.getKey().c_str(),-1,SQLITE_STATIC);
  sqlite3_bind_text(s,2,c.getContext().c_str(),-1,SQLITE_STATIC);
  sqlite3_bind_text(s,3,c.getText().c_str(),-1,SQLITE_STATIC);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}

bool Sqlite3InfoSnippetTable::update(const InfoSnippet& c)
{
  if (c.getId() < 0) return add(c);
  std::string sqlQuery = "UPDATE InfoSnippets SET key=?,context=?,note=? WHERE id=?;";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  sqlite3_bind_text(s,1,c.getKey().c_str(),-1,SQLITE_STATIC);
  sqlite3_bind_text(s,2,c.getContext().c_str(),-1,SQLITE_STATIC);
  sqlite3_bind_text(s,3,c.getText().c_str(),-1,SQLITE_STATIC);
  sqlite3_bind_int(s,4,c.getId());
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}

bool Sqlite3InfoSnippetTable::remove(int64_t id)
{
  std::string sqlQuery = "DELETE FROM InfoSnippets where id=?;";
  sqlite3_stmt* s;
  int ret = sqlite3_prepare_v2(db,sqlQuery.c_str(),sqlQuery.length(),&s,nullptr);
  sqlite3_bind_int(s,1,id);
  ret = sqlite3_step(s);
  sqlite3_finalize(s);
  return ret == SQLITE_DONE;
}


void Sqlite3InfoSnippetTable::assertTable()
{
  const char* sqlQuery = "SELECT name FROM sqlite_schema WHERE type='table' AND name='InfoSnippets';";
  const char* sqlCreate = "CREATE TABLE InfoSnippets("
                          "id INTEGER PRIMARY KEY, "
                          "key TEXT UNIQUE NOT NULL,"
                          "context TEXT UNIQUE NOT NULL,"
                          "note TEXT);";

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

