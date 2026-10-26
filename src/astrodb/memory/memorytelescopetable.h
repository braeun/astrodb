#ifndef MEMORYTELESCOPETABLE_H
#define MEMORYTELESCOPETABLE_H

#include "../telescopetable.h"
#include <map>

namespace astrodb {

class MemoryTelescopeTable: public TelescopeTable
{
public:
  MemoryTelescopeTable();
  ~MemoryTelescopeTable();

  virtual bool contains(const QString& name) override;

  virtual std::vector<QString> getNameList() override;

  virtual std::vector<Telescope> getAll() override;

  virtual Telescope get(const QString& name) override;

  virtual bool add(Telescope c) override;

  virtual bool update(const Telescope& c) override;

  virtual bool remove(const QString& name) override;

  virtual bool remove(int64_t id) override;

private:
  int64_t id;
  std::map<QString,Telescope> data;

};

} // namespace astrodb

#endif // MEMORYTELESCOPETABLE_H
