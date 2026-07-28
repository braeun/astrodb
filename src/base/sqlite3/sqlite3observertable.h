#ifndef ASTRODB_SQLITE3OBSERVERTABLE_H
#define ASTRODB_SQLITE3OBSERVERTABLE_H

#include "../observertable.h"
#include "../data/observer.h"
#include <sqlite3.h>

namespace astrodb {

class Sqlite3ObserverTable: public ObserverTable
{
public:
  Sqlite3ObserverTable(sqlite3* db);
  ~Sqlite3ObserverTable();

  virtual bool contains(const std::string& id) override;

  virtual std::vector<std::string> getIdList() override;

  virtual std::vector<Observer> getAll() override;

  virtual Observer get(const std::string& id) override;

  virtual bool add(const Observer& c) override;

  virtual bool update(const Observer& c) override;

  virtual bool remove(const std::string& id) override;

private:
  void assertTable();

  sqlite3* db;
};

} // namespace astrodb

#endif // SQLITE3OBSERVERTABLE_H
