#include "jsonobjecttable.h"
#include "json.hpp"

namespace astrodb {

JsonObjectTable::JsonObjectTable() {}

JsonObjectTable::~JsonObjectTable()
{
}

bool JsonObjectTable::contains(const std::string& id)
{
  return data.find(id) != data.end();
}

std::vector<std::string> JsonObjectTable::getIdList()
{
  std::vector<std::string> keys;
  for (const auto& [k, v] : data)
  {
    keys.push_back(k);
  }
  return keys;
}

std::vector<Object> JsonObjectTable::getAll()
{
  std::vector<Object> list;
  for (const auto& [k, v] : data)
  {
    list.push_back(v);
  }
  return list;
}

Object JsonObjectTable::get(const std::string& id)
{
  if (data.find(id) != data.end()) return data.at(id);
  return Object();
}

bool JsonObjectTable::add(const Object& c)
{
  if (data.find(c.getName()) != data.end()) return false;
  data[c.getName()] = c;
  return true;
}

bool JsonObjectTable::update(const Object& c)
{
  data[c.getName()] = c;
  return true;
}

bool JsonObjectTable::remove(const std::string& id)
{
  return data.erase(id) > 0;
}

bool JsonObjectTable::load(const nlohmann::json& json)
{
  for (const auto& j : json)
  {
    std::string name = j.value("name","");
    if (!name.empty())
    {
      Object o(name);
      data.insert(std::pair(o.getName(),o));
    }
  }
  return true;
}

nlohmann::json JsonObjectTable::save()
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
