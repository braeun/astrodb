#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <map>
#include <memory>

namespace astrodb {

class CameraTable;
class InfoSnippetTable;
class ObjectTable;
class ObserverTable;
class TelescopeTable;

class Database
{
public:
  Database() = default;
  virtual ~Database() = default;

  virtual void commit() = 0;

  virtual CameraTable* getCameraTable() = 0;

  virtual InfoSnippetTable* getInfoSnippetTable() = 0;

  virtual ObjectTable* getObjectTable() = 0;

  virtual ObserverTable* getObserverTable() = 0;

  virtual TelescopeTable* getTelescopeTable() = 0;

  static Database* connect(const std::string& driver, const std::string& db, const std::string& user, const std::string& passwd, const std::string& con="default");

  static Database* get(const std::string& con="default");

private:
  static std::map<std::string,std::unique_ptr<Database>> databases;

};

} // namespace astrodb

#endif // DATABASE_H
