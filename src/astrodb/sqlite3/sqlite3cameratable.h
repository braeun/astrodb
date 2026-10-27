#ifndef ASTRODB_SQLITE3CAMERATABLE_H
#define ASTRODB_SQLITE3CAMERATABLE_H

#include "../cameratable.h"
#include "../data/camera.h"
#include <sqlite3.h>

namespace astrodb {

class Sqlite3CameraTable: public CameraTable
{
public:
  Sqlite3CameraTable(sqlite3* db);
  ~Sqlite3CameraTable();

  virtual bool contains(const std::string& id) override;

  virtual std::vector<std::string> getIdList() override;

  virtual std::vector<Camera> getAll() override;

  virtual Camera get(const std::string& id) override;

  virtual bool add(const Camera& c) override;

  virtual bool update(const Camera& c) override;

  virtual bool remove(const std::string& id) override;

private:
  void assertTable();

  sqlite3* db;
};

} // namespace astrodb

#endif // SQLITE3CAMERATABLE_H
