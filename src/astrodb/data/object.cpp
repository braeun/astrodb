#include "object.h"

namespace astrodb {

Object::Object():
  id(-1)
{
}

Object::Object(const QString& name, int64_t id):
  id(id),
  name(name)
{
}

int64_t Object::getId() const
{
  return id;
}

void Object::setId(int64_t i)
{
  id = i;
}

const QString& Object::getName() const
{
  return name;
}

void Object::setName(const QString& n)
{
  name = n;
}

Object::operator bool() const
{
  return !name.isEmpty();
}


} // namespace astrodb
