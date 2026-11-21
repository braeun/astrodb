#ifndef SQLITE3INFOSNIPPETTABLE_H
#define SQLITE3INFOSNIPPETTABLE_H

#include <astrodb/infosnippettable.h>
#include <sqlite3.h>

namespace astrodb {

class Sqlite3InfoSnippetTable: public InfoSnippetTable
{
public:
  Sqlite3InfoSnippetTable(sqlite3* db);
  ~Sqlite3InfoSnippetTable();

  virtual std::set<std::string> getKeys() override;

  virtual std::set<std::string> getKeys(const std::string& context) override;

  virtual std::set<std::string> getContexts() override;

  virtual std::set<std::string> getContexts(const std::string& key) override;

  virtual std::vector<InfoSnippet> getSnippets(const std::string& key, const std::string& context="") override;

  virtual bool add(const InfoSnippet& c) override;

  virtual bool update(const InfoSnippet& c) override;

  virtual bool remove(int64_t id) override;

private:
  void assertTable();

  sqlite3* db;
};

} // namespace astrodb

#endif // SQLITE3INFOSNIPPETTABLE_H
