#include "observer.h"

namespace astrodb {

Observer::Observer():
  id(-1)
{
}

Observer::Observer(const QString& name, int64_t id):
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

const QString& Observer::getName() const
{
  return name;
}

void Observer::setName(const QString& n)
{
  name = n;
}

Observer::operator bool() const
{
  return !name.isEmpty();
}

} // namespace astrodb
