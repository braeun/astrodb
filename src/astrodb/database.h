#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
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

  static Database* connect(const QString& driver, const QString& db, const QString& user, const QString& passwd, const QString& con="default");

  static Database* get(const QString& con="default");

private:
  static std::map<QString,std::unique_ptr<Database>> databases;

};

} // namespace astrodb

#endif // DATABASE_H
