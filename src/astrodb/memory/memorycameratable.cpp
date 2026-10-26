#include "memorycameratable.h"
#include <QDateTime>

namespace astrodb {

MemoryCameraTable::MemoryCameraTable():
  id(0)
{
}

MemoryCameraTable::~MemoryCameraTable()
{
}

bool MemoryCameraTable::contains(const QString& name)
{
  return data.find(name) != data.end();
}

std::vector<QString> MemoryCameraTable::getNameList()
{
  std::vector<QString> keys;
  for (const auto& [k, v] : data)
  {
    keys.push_back(k);
  }
  return keys;
}

std::vector<Camera> MemoryCameraTable::getAll()
{
  std::vector<Camera> cameras;
  for (const auto& [k, v] : data)
  {
    cameras.push_back(v);
  }
  return cameras;
}

Camera MemoryCameraTable::get(const QString& name)
{
  if (data.find(name) != data.end()) return data.at(name);
  return Camera();
}

bool MemoryCameraTable::add(Camera c)
{
  if (data.find(c.getModel()) != data.end()) return false;
  ++id;
  c.setId(id);
  if (c.getModel().isEmpty())
  {
    c.setModel("Camera "+QString::number(QDateTime::currentMSecsSinceEpoch()));
  }
  data[c.getModel()] = c;
  return true;
}

bool MemoryCameraTable::update(const Camera& c)
{
  data[c.getModel()] = c;
  return true;
}

bool MemoryCameraTable::remove(const QString& name)
{
  return data.erase(name) > 0;
}

bool MemoryCameraTable::remove(int64_t id)
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
