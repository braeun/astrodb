#ifndef ASTRODB_OBSERVERTABLE_H
#define ASTRODB_OBSERVERTABLE_H

#include "data/observer.h"
#include <string>
#include <vector>

namespace astrodb {

class ObserverTable
{
public:
  ObserverTable();
  virtual ~ObserverTable() = default;

  virtual bool contains(const std::string& id) = 0;

  virtual std::vector<std::string> getIdList() = 0;

  virtual std::vector<Observer> getAll() = 0;

  virtual Observer get(const std::string& id) = 0;

  virtual bool add(const Observer& c) = 0;

  virtual bool update(const Observer& c) = 0;

  virtual bool remove(const std::string& id) = 0;

};

} // namespace astrodb

#endif // OBSERVERTABLE_H
