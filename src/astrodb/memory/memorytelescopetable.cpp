#include "memorytelescopetable.h"
#include <chrono>

namespace astrodb {

MemoryTelescopeTable::MemoryTelescopeTable():
  id(0)
{
}

MemoryTelescopeTable::~MemoryTelescopeTable()
{
}

bool MemoryTelescopeTable::contains(const std::string& name)
{
  return data.find(name) != data.end();
}

std::vector<std::string> MemoryTelescopeTable::getNameList()
{
  std::vector<std::string> keys;
  for (const auto& [k, v] : data)
  {
    keys.push_back(k);
  }
  return keys;
}

std::vector<Telescope> MemoryTelescopeTable::getAll()
{
  std::vector<Telescope> list;
  for (const auto& [k, v] : data)
  {
    list.push_back(v);
  }
  return list;
}

Telescope MemoryTelescopeTable::get(const std::string& name)
{
  if (data.find(name) != data.end()) return data.at(name);
  return Telescope();
}

bool MemoryTelescopeTable::add(Telescope c)
{
  if (data.find(c.getModel()) != data.end()) return false;
  ++id;
  c.setId(id);
  if (c.getModel().empty())
  {
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    c.setModel("Telescope "+std::to_string(ms));
  }
  data[c.getModel()] = c;
  return true;
}

bool MemoryTelescopeTable::update(const Telescope& c)
{
  data[c.getModel()] = c;
  return true;
}

bool MemoryTelescopeTable::remove(const std::string& name)
{
  return data.erase(name) > 0;
}

bool MemoryTelescopeTable::remove(int64_t id)
{
  for (const auto& [k, v] : data)
  {
    if (v.getId() == id)
    {
      return data.erase(v.getModel()) > 0;
    }
  }
  return false;
}

} // namespace astrodb
