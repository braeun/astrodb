#ifndef MEMORYOBJECTTABLE_H
#define MEMORYOBJECTTABLE_H

#include "../objecttable.h"
#include <map>

namespace astrodb {

class MemoryObjectTable: public ObjectTable
{
public:
  MemoryObjectTable();
  ~MemoryObjectTable();

  virtual bool contains(const QString& name) override;

  virtual std::vector<QString> getNameList() override;

  virtual std::vector<Object> getAll() override;

  virtual Object get(const QString& name) override;

  virtual bool add(Object c) override;

  virtual bool update(const Object& c) override;

  virtual bool remove(const QString& name) override;

  virtual bool remove(int64_t id) override;

private:
  int64_t id;
  std::map<QString,Object> data;

};

} // namespace astrodb

#endif // MEMORYOBJECTTABLE_H
