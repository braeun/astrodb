#ifndef ASTRODB_SQLITE3TELESCOPETABLE_H
#define ASTRODB_SQLITE3TELESCOPETABLE_H

#include "../telescopetable.h"
#include "../data/telescope.h"
#include <sqlite3.h>

namespace astrodb {

class Sqlite3TelescopeTable: public TelescopeTable
{
public:
  Sqlite3TelescopeTable(sqlite3* db);
  ~Sqlite3TelescopeTable();

  virtual bool contains(const std::string& id) override;

  virtual std::vector<std::string> getIdList() override;

  virtual std::vector<Telescope> getAll() override;

  virtual Telescope get(const std::string& id) override;

  virtual bool add(const Telescope& c) override;

  virtual bool update(const Telescope& c) override;

  virtual bool remove(const std::string& id) override;

private:
  void assertTable();

  sqlite3* db;
};

} // namespace astrodb

#endif // SQLITE3TELESCOPETABLE_H
