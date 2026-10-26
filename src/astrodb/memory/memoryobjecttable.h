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

  virtual bool contains(const std::string& name) override;

  virtual std::vector<std::string> getNameList() override;

  virtual std::vector<Object> getAll() override;

  virtual Object get(const std::string& name) override;

  virtual bool add(Object c) override;

  virtual bool update(const Object& c) override;

  virtual bool remove(const std::string& name) override;

  virtual bool remove(int64_t id) override;

private:
  int64_t id;
  std::map<std::string,Object> data;

};

} // namespace astrodb

#endif // MEMORYOBJECTTABLE_H
