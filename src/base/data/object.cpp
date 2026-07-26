#include "object.h"

namespace astrodb {

Object::Object()
{
}

Object::Object(const std::string& name):
  name(name)
{
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
