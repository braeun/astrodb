#ifndef ASTRODB_JSONDATABASE_H
#define ASTRODB_JSONDATABASE_H

#include "../database.h"
#include <memory>
#include <mutex>
#include <string>

namespace astrodb {

class MemoryCameraTable;
class MemoryInfoSnippetTable;
class MemoryObjectTable;
class MemoryObserverTable;
class MemoryTelescopeTable;

class JsonDatabase: public Database
{
public:
  JsonDatabase(const std::string& filename);
  virtual ~JsonDatabase();

  virtual void commit() override;

  virtual CameraTable* getCameraTable() override;

  virtual InfoSnippetTable* getInfoSnippetTable() override;

  virtual ObjectTable* getObjectTable() override;

  virtual ObserverTable* getObserverTable() override;

  virtual TelescopeTable* getTelescopeTable() override;

private:
  bool load();
  bool save();

  std::string filename;
  std::mutex writelock;
  std::unique_ptr<MemoryCameraTable> cameraTable;
  std::unique_ptr<MemoryInfoSnippetTable> infoSnippetTable;
  std::unique_ptr<MemoryObjectTable> objectTable;
  std::unique_ptr<MemoryObserverTable> observerTable;
  std::unique_ptr<MemoryTelescopeTable> telescopeTable;
};

} // namespace astrodb

#endif // JSONDATABASE_H
