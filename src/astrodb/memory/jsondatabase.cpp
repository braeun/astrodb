#include "jsondatabase.h"
#include "memorycameratable.h"
#include "memoryinfosnippettable.h"
#include "memoryobjecttable.h"
#include "memoryobservertable.h"
#include "memorytelescopetable.h"
#include "json.hpp"
#include "../utils.h"
#include <ctime>
#include <fstream>

namespace astrodb {

JsonDatabase::JsonDatabase(const std::string& fn):
  filename(fn)
{
  if (filename.empty())
  {
    filename = utils::getUserDataPath() + "/astrodb.json";
  }
  cameraTable = std::make_unique<MemoryCameraTable>();
  infoSnippetTable = std::make_unique<MemoryInfoSnippetTable>();
  objectTable = std::make_unique<MemoryObjectTable>();
  observerTable = std::make_unique<MemoryObserverTable>();
  telescopeTable = std::make_unique<MemoryTelescopeTable>();
  load();
}

JsonDatabase::~JsonDatabase()
{
  save();
}

void JsonDatabase::commit()
{
  save();
}

CameraTable* JsonDatabase::getCameraTable()
{
  return cameraTable.get();
}

InfoSnippetTable* JsonDatabase::getInfoSnippetTable()
{
  return infoSnippetTable.get();
}

ObjectTable* JsonDatabase::getObjectTable()
{
  return objectTable.get();
}

ObserverTable* JsonDatabase::getObserverTable()
{
  return observerTable.get();
}

TelescopeTable* JsonDatabase::getTelescopeTable()
{
  return telescopeTable.get();
}

bool JsonDatabase::load()
{
  if (!std::filesystem::exists(filename))
  {
//    throw std::runtime_error("File '"+filename.toStdString()+"' not found");
    return false;
  }
  std::ifstream is(filename);
  nlohmann::json json = nlohmann::json::parse(is);
  is.close();
  if (json.contains("cameras"))
  {
    for (const auto& j : json.at("cameras"))
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
        cameraTable->add(c);
      }
    }
  }
  if (json.contains("infos"))
  {
    for (const auto& j : json.at("infos"))
    {
      std::string key = j.value("key","");
      std::string context = j.value("context","");
      std::string text = j.value("text","");
      InfoSnippet s(key,context,text);
      infoSnippetTable->add(s);
    }
  }
  if (json.contains("objects"))
  {
    for (const auto& j : json.at("objects"))
    {
      std::string name = j.value("name","");
      if (!name.empty())
      {
        Object o(name);
        objectTable->add(o);
      }
    }
  }
  if (json.contains("observers"))
  {
    for (const auto& j : json.at("observers"))
    {
      std::string name = j.value("name","");
      if (!name.empty())
      {
        Observer o(name);
        observerTable->add(o);
      }
    }
  }
  if (json.contains("telescopes"))
  {
    for (const auto& j : json.at("telescopes"))
    {
      std::string model = j.value("model","");
      if (!model.empty())
      {
        double f = j.value("f",0.0);
        double d = j.value("d",0.0);
        Telescope c(model,f,d);
        telescopeTable->add(c);
      }
    }
  }
  return true;
}

bool JsonDatabase::save()
{
  std::lock_guard<std::mutex> lock(writelock);
  nlohmann::json json;
  json["timestamp"] = std::time(nullptr);
  nlohmann::json jc;
  for (const auto& v : cameraTable->getAll())
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
    jc.push_back(js);
  }
  json["cameras"] = jc;
  nlohmann::json ji;
  for (const auto& v : infoSnippetTable->getSnippets("",""))
  {
    nlohmann::json js;
    js["key"] = v.getKey();
    js["context"] = v.getContext();
    js["text"] = v.getText();
    ji.push_back(js);
  }
  json["infos"] = ji;
  nlohmann::json jobj;
  for (const auto& v : objectTable->getAll())
  {
    nlohmann::json js;
    js["name"] = v.getName();
    jobj.push_back(js);
  }
  json["objects"] = jobj;
  nlohmann::json jobs;
  for (const auto& v : observerTable->getAll())
  {
    nlohmann::json js;
    js["name"] = v.getName();
    jobs.push_back(js);
  }
  json["observers"] = jobs;
  nlohmann::json jt;
  for (const auto& v : telescopeTable->getAll())
  {
    nlohmann::json js;
    js["model"] = v.getModel();
    js["f"] = v.getFocalLength();
    js["d"] = v.getAperture();
    jt.push_back(js);
  }
  json["telescopes"] = jt;
  std::ofstream s(filename);
  if (!s.fail())
  {
    s << std::setw(2) << json;
    s.close();
    return true;
  }
  return false;
}



} // namespace astrodb


