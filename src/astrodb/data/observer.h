#ifndef ASTRODB_OBSERVER_H
#define ASTRODB_OBSERVER_H

#include <cstdint>
#include <QString>

namespace astrodb {

class Observer
{
public:
  Observer();
  Observer(const QString& name, int64_t id=-1);

  int64_t getId() const;

  void setId(int64_t i);

  const QString& getName() const;

  void setName(const QString& n);

  explicit operator bool() const;

private:
  int64_t id;
  QString name;
};

} // namespace astrodb

#endif // OBSERVER_H
