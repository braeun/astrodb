#ifndef DATABASE_H
#define DATABASE_H


namespace astrodb {

class CameraTable;
class ObjectTable;
class ObserverTable;
class TelescopeTable;

class Database
{
public:
  Database() = default;
  virtual ~Database() = default;

  virtual CameraTable* getCameraTable() = 0;

  virtual ObjectTable* getObjectTable() = 0;

  virtual ObserverTable* getObserverTable() = 0;

  virtual TelescopeTable* getTelescopeTable() = 0;

};

} // namespace astrodb

#endif // DATABASE_H
