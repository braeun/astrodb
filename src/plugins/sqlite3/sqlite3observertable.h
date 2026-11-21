#ifndef ASTRODB_SQLITE3OBSERVERTABLE_H
#define ASTRODB_SQLITE3OBSERVERTABLE_H

#include <astrodb/observertable.h>
#include <astrodb/data/observer.h>
#include <sqlite3.h>

namespace astrodb {

class Sqlite3ObserverTable: public ObserverTable
{
public:
  Sqlite3ObserverTable(sqlite3* db);
  ~Sqlite3ObserverTable();

  virtual bool contains(const std::string& id) override;

  virtual std::vector<std::string> getNameList() override;

  virtual std::vector<Observer> getAll() override;

  virtual Observer get(const std::string& id) override;

  virtual bool add(Observer c) override;

  virtual bool update(const Observer& c) override;

  virtual bool remove(const std::string& id) override;

  virtual bool remove(int64_t id) override;

private:
  void assertTable();

  sqlite3* db;
};

} // namespace astrodb

#endif // SQLITE3OBSERVERTABLE_H
