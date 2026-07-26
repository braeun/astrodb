#ifndef ASTRODB_OBSERVER_H
#define ASTRODB_OBSERVER_H

#include <string>

namespace astrodb {

class Observer
{
public:
  Observer();
  Observer(const std::string& name);

  const std::string& getName() const;
  void setName(const std::string& n);

  explicit operator bool() const;

private:
  std::string name;
};

} // namespace astrodb

#endif // OBSERVER_H
