#include "observer.h"

namespace astrodb {

Observer::Observer():
  id(-1)
{
}

Observer::Observer(const std::string& name, int64_t id):
  id(id),
  name(name)
{
}

int64_t Observer::getId() const
{
  return id;
}

void Observer::setId(int64_t i)
{
  id = i;
}

const std::string& Observer::getName() const
{
  return name;
}

void Observer::setName(const std::string& n)
{
  name = n;
}

Observer::operator bool() const
{
  return !name.empty();
}

} // namespace astrodb
