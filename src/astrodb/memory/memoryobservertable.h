#ifndef MEMORYOBSERVERTABLE_H
#define MEMORYOBSERVERTABLE_H

#include "../observertable.h"
#include <map>

namespace astrodb {

class MemoryObserverTable: public ObserverTable
{
public:
  MemoryObserverTable();
  ~MemoryObserverTable();

  virtual bool contains(const QString& name) override;

  virtual std::vector<QString> getNameList() override;

  virtual std::vector<Observer> getAll() override;

  virtual Observer get(const QString& name) override;

  virtual bool add(Observer c) override;

  virtual bool update(const Observer& c) override;

  virtual bool remove(const QString& name) override;

  virtual bool remove(int64_t id) override;

private:
  int64_t id;
  std::map<QString,Observer> data;

};

} // namespace astrodb

#endif // MEMORYOBSERVERTABLE_H
