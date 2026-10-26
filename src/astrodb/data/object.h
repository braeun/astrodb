#ifndef ASTRODB_OBJECT_H
#define ASTRODB_OBJECT_H

#include <cstdint>
#include <string>

namespace astrodb {

class Object
{
public:
  Object();
  Object(const std::string& name, int64_t id=-1);

  int64_t getId() const;

  void setId(int64_t i);

  const std::string& getName() const;

  void setName(const std::string& n);

  explicit operator bool() const;

private:
  int64_t id;
  std::string name;
};

} // namespace astrodb

#endif // OBJECT_H
