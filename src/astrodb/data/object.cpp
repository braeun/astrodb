#include "object.h"

namespace astrodb {

Object::Object():
  id(-1)
{
}

Object::Object(const std::string& name, int64_t id):
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

const std::string& Object::getName() const
{
  return name;
}

void Object::setName(const std::string& n)
{
  name = n;
}

Object::operator bool() const
{
  return !name.empty();
}


} // namespace astrodb
