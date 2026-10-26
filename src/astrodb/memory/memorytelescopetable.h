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

  virtual bool contains(const std::string& name) override;

  virtual std::vector<std::string> getNameList() override;

  virtual std::vector<Telescope> getAll() override;

  virtual Telescope get(const std::string& name) override;

  virtual bool add(Telescope c) override;

  virtual bool update(const Telescope& c) override;

  virtual bool remove(const std::string& name) override;

  virtual bool remove(int64_t id) override;

private:
  int64_t id;
  std::map<std::string,Telescope> data;

};

} // namespace astrodb

#endif // MEMORYTELESCOPETABLE_H
