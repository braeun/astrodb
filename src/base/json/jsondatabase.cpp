#include "jsondatabase.h"
#include "jsoncameratable.h"
#include "jsonobjecttable.h"
#include "jsonobservertable.h"
#include "jsontelescopetable.h"
#include "json.hpp"
#include <ctime>
#include <fstream>

namespace astrodb {

JsonDatabase::JsonDatabase(const std::string& filename):
  filename(filename)
{
  cameraTable = std::make_unique<JsonCameraTable>();
  objectTable = std::make_unique<JsonObjectTable>();
  observerTable = std::make_unique<JsonObserverTable>();
  telescopeTable = std::make_unique<JsonTelescopeTable>();
  load();
}

JsonDatabase::~JsonDatabase()
{
  save();
}

CameraTable* JsonDatabase::getCameraTable()
{
  return cameraTable.get();
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
  if (filename.empty() || !std::filesystem::exists(filename))
  {
    throw std::runtime_error("File '"+filename+"' not found");
  }
  std::ifstream is(filename);
  nlohmann::json json = nlohmann::json::parse(is);
  is.close();
  if (json.contains("cameras"))
  {
    cameraTable->load(json.at("cameras"));
  }
  if (json.contains("objects"))
  {
    objectTable->load(json.at("objects"));
  }
  if (json.contains("observers"))
  {
    observerTable->load(json.at("observers"));
  }
  if (json.contains("telescopes"))
  {
    telescopeTable->load(json.at("telescopes"));
  }
  return true;
}

bool JsonDatabase::save()
{
  std::lock_guard<std::mutex> lock(writelock);
  nlohmann::json json;
  json["timestamp"] = std::time(nullptr);
  json["cameras"] = cameraTable->save();
  json["objects"] = objectTable->save();
  json["observers"] = observerTable->save();
  json["telescopes"] = telescopeTable->save();
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


