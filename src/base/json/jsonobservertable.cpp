#include "jsonobservertable.h"
#include "json.hpp"

namespace astrodb {

JsonObserverTable::JsonObserverTable() {}

JsonObserverTable::~JsonObserverTable()
{
}

bool JsonObserverTable::contains(const std::string& id)
{
  return data.find(id) != data.end();
}

std::vector<std::string> JsonObserverTable::getIdList()
{
  std::vector<std::string> keys;
  for (const auto& [k, v] : data)
  {
    keys.push_back(k);
  }
  return keys;
}

std::vector<Observer> JsonObserverTable::getAll()
{
  std::vector<Observer> list;
  for (const auto& [k, v] : data)
  {
    list.push_back(v);
  }
  return list;
}

Observer JsonObserverTable::get(const std::string& id)
{
  if (data.find(id) != data.end()) return data.at(id);
  return Observer();
}

bool JsonObserverTable::add(const Observer& c)
{
  if (data.find(c.getName()) != data.end()) return false;
  data[c.getName()] = c;
  return true;
}

bool JsonObserverTable::update(const Observer& c)
{
  data[c.getName()] = c;
  return true;
}

bool JsonObserverTable::remove(const std::string& id)
{
  return data.erase(id) > 0;
}

bool JsonObserverTable::load(const nlohmann::json& json)
{
  for (const auto& j : json)
  {
    std::string name = j.value("name","");
    if (!name.empty())
    {
      Observer o(name);
      data.insert(std::pair(o.getName(),o));
    }
  }
  return true;
}

nlohmann::json JsonObserverTable::save()
{
  nlohmann::json json;
  for (const auto& [k,v] : data)
  {
    nlohmann::json js;
    js["name"] = v.getName();
    json.push_back(js);
  }
  return json;
}

} // namespace astrodb
