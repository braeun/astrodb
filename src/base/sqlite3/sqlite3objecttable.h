#ifndef SQLITE3OBJECTTABLE_H
#define SQLITE3OBJECTTABLE_H

#include "../objecttable.h"
#include "../data/object.h"
#include <sqlite3.h>

namespace astrodb {

class Sqlite3ObjectTable: public ObjectTable
{
public:
  Sqlite3ObjectTable(sqlite3* db);
  ~Sqlite3ObjectTable();

  virtual bool contains(const std::string& id) override;

  virtual std::vector<std::string> getIdList() override;

  virtual std::vector<Object> getAll() override;

  virtual Object get(const std::string& id) override;

  virtual bool add(const Object& c) override;

  virtual bool update(const Object& c) override;

  virtual bool remove(const std::string& id) override;

private:
  void assertTable();

  sqlite3* db;
};

} // namespace astrodb

#endif // SQLITE3OBJECTTABLE_H
