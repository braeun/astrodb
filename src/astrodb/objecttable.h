#ifndef ASTRODB_OBJECTTABLE_H
#define ASTRODB_OBJECTTABLE_H

#include "data/object.h"
#include <QString>
#include <vector>

namespace astrodb {

class ObjectTable
{
public:
  ObjectTable();
  virtual ~ObjectTable() = default;

  virtual bool contains(const QString& id) = 0;

  virtual std::vector<QString> getNameList() = 0;

  virtual std::vector<Object> getAll() = 0;

  virtual Object get(const QString& id) = 0;

  virtual bool add(Object c) = 0;

  virtual bool update(const Object& c) = 0;

  virtual bool remove(const QString& id) = 0;

  virtual bool remove(int64_t id) = 0;

};

} // namespace astrodb

#endif // OBJECTTABLE_H
