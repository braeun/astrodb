#ifndef ASTRODB_OBSERVERTABLE_H
#define ASTRODB_OBSERVERTABLE_H

#include "data/observer.h"
#include <QString>
#include <vector>

namespace astrodb {

class ObserverTable
{
public:
  ObserverTable();
  virtual ~ObserverTable() = default;

  virtual bool contains(const QString& id) = 0;

  virtual std::vector<QString> getNameList() = 0;

  virtual std::vector<Observer> getAll() = 0;

  virtual Observer get(const QString& id) = 0;

  virtual bool add(Observer c) = 0;

  virtual bool update(const Observer& c) = 0;

  virtual bool remove(const QString& id) = 0;

  virtual bool remove(int64_t id) = 0;

};

} // namespace astrodb

#endif // OBSERVERTABLE_H
