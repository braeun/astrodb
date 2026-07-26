#include "observer.h"

namespace astrodb {

Observer::Observer()
{
}

Observer::Observer(const std::string& name):
  name(name)
{}

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
