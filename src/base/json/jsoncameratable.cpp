#include "jsoncameratable.h"
#include "json.hpp"

namespace astrodb {

JsonCameraTable::JsonCameraTable()
{
}

JsonCameraTable::~JsonCameraTable()
{
}

bool JsonCameraTable::contains(const std::string& id)
{
  return data.find(id) != data.end();
}

std::vector<std::string> JsonCameraTable::getIdList()
{
  std::vector<std::string> keys;
  for (const auto& [k, v] : data)
  {
    keys.push_back(k);
  }
  return keys;
}

std::vector<Camera> JsonCameraTable::getAll()
{
  std::vector<Camera> cameras;
  for (const auto& [k, v] : data)
  {
    cameras.push_back(v);
  }
  return cameras;
}

Camera JsonCameraTable::get(const std::string& id)
{
  if (data.find(id) != data.end()) return data.at(id);
  return Camera();
}

bool JsonCameraTable::add(const Camera& c)
{
  if (data.find(c.getModel()) != data.end()) return false;
  data[c.getModel()] = c;
  return true;
}

bool JsonCameraTable::update(const Camera& c)
{
  data[c.getModel()] = c;
  return true;
}

bool JsonCameraTable::remove(const std::string& id)
{
  return data.erase(id) > 0;
}

bool JsonCameraTable::load(const nlohmann::json& json)
{
  for (const auto& j : json)
  {
    std::string model = j.value("model","");
    if (!model.empty())
    {
      int w = j.value("width",0);
      int h = j.value("height",0);
      Camera c(model,w,h);
      c.setPixelWidth(j.value("pixelwidth",0.0));
      c.setPixelHeight(j.value("pixelheight",0.0));
      c.setSensorWidth(j.value("sensorwidth",0.0));
      c.setSensorHeight(j.value("sensorheight",0.0));
      c.setBpp(j.value("bpp",8));
      data.insert(std::pair(c.getModel(),c));
    }
  }
  return true;
}

nlohmann::json JsonCameraTable::save()
{
  nlohmann::json json;
  for (const auto& [k,v] : data)
  {
    nlohmann::json js;
    js["model"] = v.getModel();
    js["width"] = v.getWidth();
    js["height"] = v.getHeight();
    js["pixelwidth"] = v.getPixelWidth();
    js["pixelheight"] = v.getPixelHeight();
    js["sensorwidth"] = v.getSensorWidth();
    js["sensorheight"] = v.getSensorHeight();
    js["bpp"] = v.getBpp();
    json.push_back(js);
  }
  return json;
}


} // namespace astrodb

