#ifndef ASTRODB_OBJECTTABLE_H
#define ASTRODB_OBJECTTABLE_H

#include "data/object.h"
#include <string>
#include <vector>

namespace astrodb {

class ObjectTable
{
public:
  ObjectTable();
  virtual ~ObjectTable() = default;

  virtual bool contains(const std::string& id) = 0;

  virtual std::vector<std::string> getIdList() = 0;

  virtual std::vector<Object> getAll() = 0;

  virtual Object get(const std::string& id) = 0;

  virtual bool add(const Object& c) = 0;

  virtual bool update(const Object& c) = 0;

  virtual bool remove(const std::string& id) = 0;

};

} // namespace astrodb

#endif // OBJECTTABLE_H
