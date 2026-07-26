#ifndef ASTRODB_OBJECT_H
#define ASTRODB_OBJECT_H

#include <string>

namespace astrodb {

class Object
{
public:
  Object();
  Object(const std::string& name);

  const std::string& getName() const;

  void setName(const std::string& n);

  explicit operator bool() const;

private:
  std::string name;
};

} // namespace astrodb

#endif // OBJECT_H
