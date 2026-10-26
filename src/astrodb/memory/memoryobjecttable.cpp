#include "memoryobjecttable.h"
#include <QDateTime>

namespace astrodb {

MemoryObjectTable::MemoryObjectTable():
  id(0)
{
}

MemoryObjectTable::~MemoryObjectTable()
{
}

bool MemoryObjectTable::contains(const QString& name)
{
  return data.find(name) != data.end();
}

std::vector<QString> MemoryObjectTable::getNameList()
{
  std::vector<QString> keys;
  for (const auto& [k, v] : data)
  {
    keys.push_back(k);
  }
  return keys;
}

std::vector<Object> MemoryObjectTable::getAll()
{
  std::vector<Object> list;
  for (const auto& [k, v] : data)
  {
    list.push_back(v);
  }
  return list;
}

Object MemoryObjectTable::get(const QString& name)
{
  if (data.find(name) != data.end()) return data.at(name);
  return Object();
}

bool MemoryObjectTable::add(Object c)
{
  if (data.find(c.getName()) != data.end()) return false;
  ++id;
  c.setId(id);
  if (c.getName().isEmpty())
  {
    c.setName("Object "+QString::number(QDateTime::currentMSecsSinceEpoch()));
  }
  data[c.getName()] = c;
  return true;
}

bool MemoryObjectTable::update(const Object& c)
{
  data[c.getName()] = c;
  return true;
}

bool MemoryObjectTable::remove(const QString& name)
{
  return data.erase(name) > 0;
}

bool MemoryObjectTable::remove(int64_t id)
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
