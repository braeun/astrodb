#ifndef DATABASEQT6_H
#define DATABASEQT6_H

#include "cameratableqt.h"
#include "infosnippettableqt.h"
#include "objecttableqt.h"
#include "observertableqt.h"
#include "telescopetableqt.h"
#include <astrodb/database.h>
#include <QString>
#include <memory>

namespace astrodb {

class DatabaseQt: public Database
{
public:
  DatabaseQt(const std::string& driver, const std::string& dbname, const std::string& user, const std::string& passwd);

  virtual std::string getBackend() const override;

  virtual std::string getName() const override;

  virtual void commit() override;

  virtual CameraTable* getCameraTable() override;

  virtual InfoSnippetTable* getInfoSnippetTable() override;

  virtual ObjectTable* getObjectTable() override;

  virtual ObserverTable* getObserverTable() override;

  virtual TelescopeTable* getTelescopeTable() override;

private:
  void setupSQLite(const std::string& dbname, const std::string& user, const std::string& passwd);

  QString con;
  std::unique_ptr<CameraTableQt> cameraTable;
  std::unique_ptr<InfoSnippetTableQt> infoSnippetTable;
  std::unique_ptr<ObjectTableQt> objectTable;
  std::unique_ptr<ObserverTableQt> observerTable;
  std::unique_ptr<TelescopeTableQt> telescopeTable;
};

} // namespace astrodb

#endif // DATABASEQT6_H
