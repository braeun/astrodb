#include "jsontelescopetable.h"
#include "json.hpp"

namespace astrodb {

JsonTelescopeTable::JsonTelescopeTable()
{
}

JsonTelescopeTable::~JsonTelescopeTable()
{
}

bool JsonTelescopeTable::contains(const std::string& id)
{
  return data.find(id) != data.end();
}

std::vector<std::string> JsonTelescopeTable::getIdList()
{
  std::vector<std::string> keys;
  for (const auto& [k, v] : data)
  {
    keys.push_back(k);
  }
  return keys;
}

std::vector<Telescope> JsonTelescopeTable::getAll()
{
  std::vector<Telescope> list;
  for (const auto& [k, v] : data)
  {
    list.push_back(v);
  }
  return list;
}

Telescope JsonTelescopeTable::get(const std::string& id)
{
  if (data.find(id) != data.end()) return data.at(id);
  return Telescope();
}

bool JsonTelescopeTable::add(const Telescope& c)
{
  if (data.find(c.getModel()) != data.end()) return false;
  data[c.getModel()] = c;
  return true;
}

bool JsonTelescopeTable::update(const Telescope& c)
{
  data[c.getModel()] = c;
  return true;
}

bool JsonTelescopeTable::remove(const std::string& id)
{
  return data.erase(id) > 0;
}

bool JsonTelescopeTable::load(const nlohmann::json& json)
{
  for (const auto& j : json)
  {
    std::string model = j.value("model","");
    if (!model.empty())
    {
      double f = j.value("f",0.0);
      double d = j.value("d",0.0);
      Telescope c(model,f,d);
      data.insert(std::pair(c.getModel(),c));
    }
  }
  return true;
}

nlohmann::json JsonTelescopeTable::save()
{
  nlohmann::json json;
  for (const auto& [k,v] : data)
  {
    nlohmann::json js;
    js["model"] = v.getModel();
    js["f"] = v.getFocalLength();
    js["d"] = v.getAperture();
    json.push_back(js);
  }
  return json;
}

} // namespace astrodb
