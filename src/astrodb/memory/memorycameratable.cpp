#include "memorycameratable.h"
#include <chrono>

namespace astrodb {

MemoryCameraTable::MemoryCameraTable():
  id(0)
{
}

MemoryCameraTable::~MemoryCameraTable()
{
}

bool MemoryCameraTable::contains(const std::string& name)
{
  return data.find(name) != data.end();
}

std::vector<std::string> MemoryCameraTable::getNameList()
{
  std::vector<std::string> keys;
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

Camera MemoryCameraTable::get(const std::string& name)
{
  if (data.find(name) != data.end()) return data.at(name);
  return Camera();
}

bool MemoryCameraTable::add(Camera c)
{
  if (data.find(c.getModel()) != data.end()) return false;
  ++id;
  c.setId(id);
  if (c.getModel().empty())
  {
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    c.setModel("Camera "+std::to_string(ms));
  }
  data[c.getModel()] = c;
  return true;
}

bool MemoryCameraTable::update(const Camera& c)
{
  data[c.getModel()] = c;
  return true;
}

bool MemoryCameraTable::remove(const std::string& name)
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
