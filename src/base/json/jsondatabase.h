#ifndef ASTRODB_JSONDATABASE_H
#define ASTRODB_JSONDATABASE_H

#include "../database.h"
#include <memory>
#include <mutex>
#include <string>

namespace astrodb {

class CameraTable;
class JsonCameraTable;
class JsonObjectTable;
class JsonObserverTable;
class JsonTelescopeTable;
class ObjectTable;
class ObserverTable;
class TelescopeTable;

class JsonDatabase: public Database
{
public:
  JsonDatabase(const std::string& filename);
  virtual ~JsonDatabase();

  virtual CameraTable* getCameraTable() override;

  virtual ObjectTable* getObjectTable() override;

  virtual ObserverTable* getObserverTable() override;

  virtual TelescopeTable* getTelescopeTable() override;

private:
  bool load();
  bool save();

  std::string filename;
  std::mutex writelock;
  std::unique_ptr<JsonCameraTable> cameraTable;
  std::unique_ptr<JsonObjectTable> objectTable;
  std::unique_ptr<JsonObserverTable> observerTable;
  std::unique_ptr<JsonTelescopeTable> telescopeTable;
};

} // namespace astrodb

#endif // JSONDATABASE_H
