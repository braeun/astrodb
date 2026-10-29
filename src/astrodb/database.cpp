#include "database.h"
#include "plugin.h"
#include "utils.h"
#include "memory/jsondatabase.h"
#include <algorithm>
#include <dlfcn.h>
#include <filesystem>
#include <iostream>

namespace astrodb {

static const char* so_extension = ".so";

const char* Database::VAR_ASTRODB_PLUGIN_PATH = "ASTRODB_PLUGIN_PATH";

std::map<std::string,std::unique_ptr<Database>> Database::databases;
bool Database::pluginsInititalized = false;
std::vector<std::unique_ptr<Database::PluginHandler>> Database::plugins;
bool Database::envAdded = false;
std::vector<std::string> Database::searchPath{
  "/usr/lib/astrodb",
  "/usr/lib64/astrodb",
  "/usr/local/lib/astrodb",
  "/usr/local/lib64/astrodb"
};

std::vector<std::string> Database::getDrivers()
{
  std::vector<std::string> list;
  initialize();
  list.push_back("JSON");
  for (const auto& p : plugins)
  {
    auto l = p->getDrivers();
    list.insert(list.end(),l.begin(),l.end());
  }
  return list;
}

Database* Database::connect(const std::string& driver, const std::string& db, const std::string& user, const std::string& passwd, const std::string& con)
{
  initialize();
  auto it = databases.find(con);
  if (it != databases.end())
  {
    databases.erase(it);
  }
  std::unique_ptr<Database> p;
  std::string d = driver;
  std::transform(d.begin(),d.end(),d.begin(),::tolower);
  if (d == "json")
  {
    p.reset(new JsonDatabase(db));
  }
  else
  {
    for (const auto& h : plugins)
    {
      if (h->handlesDriver(driver))
      {
        p = h->connect(driver,db,user,passwd);
        break;
      }
    }
  }
  if (p)
  {
    databases[con] = std::move(p);
  }
  return get(con);
}

Database* Database::get(const std::string& con)
{
  initialize();
  if (databases.find(con) != databases.end())
  {
    return databases.at(con).get();
  }
  return nullptr;
}

void Database::initialize()
{
  if (!pluginsInititalized)
  {
    if (!envAdded)
    {
      const char* clibpath = getenv(VAR_ASTRODB_PLUGIN_PATH);
      if (clibpath)
      {
        std::cout << clibpath << std::endl;
        std::vector<std::string> dirs = utils::split(clibpath,':',true);
        searchPath.insert(searchPath.begin(),dirs.begin(),dirs.end());
      }
      envAdded = true;
    }
    scan();
    pluginsInititalized = true;
  }
}

void Database::scan()
{
  for (const auto& path : searchPath)
  {
    scan(path);
  }
}

void Database::scan(const std::string &dir)
{
  //  std::cout << "Scanning path " << dir << std::endl;
  std::filesystem::path path = dir;
  if (!std::filesystem::exists(path)) return;
  for (const auto & entry : std::filesystem::directory_iterator(path))
  {
    //    std::cout << entry.path() << std::endl;
    if (entry.is_directory())
    {
      scan(dir+"/"+entry.path().filename().string());
    }
    else if (entry.path().extension() == so_extension && entry.path().stem().string().find("-noload") == std::string::npos)
    {
      try
      {
        auto h = std::make_unique<PluginHandler>(entry.path().string());
        if (*h.get())
        {
          std::cout << "added plugin: " << h->getPluginName() << " " << h->getPluginVersion() << std::endl;
          plugins.push_back(std::move(h));
        }
      }
      catch (const std::exception& ex)
      {
        std::cerr << "failed to load plugin " << entry.path().filename().string() << ": " << ex.what() << std::endl;
      }
    }
  }
}






Database::PluginHandler::PluginHandler(const std::string& name):
  filename(name),
  instance(nullptr)
{
  handle = dlopen(name.c_str(), RTLD_NOW|RTLD_GLOBAL);
  if (handle)
  {
    auto fn_isplugin = (bool(*)())dlsym(handle,"isAstroDBPlugin");
    if (fn_isplugin)
    {
      auto fn_load = (Plugin* (*)())dlsym(handle,"load");
      if (fn_load)
      {
        try
        {
          instance = fn_load();
        }
        catch (std::exception& ex)
        {
          std::cerr << ex.what() << std::endl;
          instance = nullptr;
        }
      }
    }
    if (!instance)
    {
      dlclose(handle);
      handle = nullptr;
    }
  }
  else
  {
    std::cerr << dlerror() << std::endl;
  }
}

Database::PluginHandler::PluginHandler(Plugin* plugin):
  handle(nullptr),
  filename("application"),
  instance(plugin)
{
}

Database::PluginHandler::~PluginHandler()
{
  delete instance;
  instance = nullptr;
  if (handle) dlclose(handle);
  handle = nullptr;
}

std::string Database::PluginHandler::getFilename() const
{
  return filename;
}

std::string Database::PluginHandler::getPluginName() const
{
  if (instance) return instance->getName();
  return "error";
}

std::string Database::PluginHandler::getPluginVersion() const
{
  if (instance) return instance->getVersion();
  return "error";
}

bool Database::PluginHandler::handlesDriver(const std::string& driver) const
{
  for (const auto& d : getDrivers())
  {
    if (d == driver) return true;
  }
  return false;
}

std::vector<std::string> Database::PluginHandler::getDrivers() const
{
  if (instance) return instance->getDrivers();
  return std::vector<std::string>();
}

std::unique_ptr<Database> Database::PluginHandler::connect(const std::string& driver, const std::string& db, const std::string& user, const std::string& passwd) const
{
  if (instance) return instance->connect(driver,db,user,passwd);
  return std::unique_ptr<Database>();
}


} // namespace astrodb
