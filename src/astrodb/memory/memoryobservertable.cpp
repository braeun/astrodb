#include "memoryobservertable.h"
#include <chrono>

namespace astrodb {

MemoryObserverTable::MemoryObserverTable():
  id(0)
{
}

MemoryObserverTable::~MemoryObserverTable()
{
}

bool MemoryObserverTable::contains(const std::string& name)
{
  return data.find(name) != data.end();
}

std::vector<std::string> MemoryObserverTable::getNameList()
{
  std::vector<std::string> keys;
  for (const auto& [k, v] : data)
  {
    keys.push_back(k);
  }
  return keys;
}

std::vector<Observer> MemoryObserverTable::getAll()
{
  std::vector<Observer> list;
  for (const auto& [k, v] : data)
  {
    list.push_back(v);
  }
  return list;
}

Observer MemoryObserverTable::get(const std::string& name)
{
  if (data.find(name) != data.end()) return data.at(name);
  return Observer();
}

bool MemoryObserverTable::add(Observer c)
{
  if (data.find(c.getName()) != data.end()) return false;
  ++id;
  c.setId(id);
  if (c.getName().empty())
  {
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    c.setName("Observer "+std::to_string(ms));
  }
  data[c.getName()] = c;
  return true;
}

bool MemoryObserverTable::update(const Observer& c)
{
  data[c.getName()] = c;
  return true;
}

bool MemoryObserverTable::remove(const std::string& name)
{
  return data.erase(name) > 0;
}

bool MemoryObserverTable::remove(int64_t id)
{
  for (const auto& [k, v] : data)
  {
    if (v.getId() == id)
    {
      return data.erase(v.getName()) > 0;
    }
  }
  return false;
}

} // namespace astrodb
