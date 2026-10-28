#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <map>
#include <memory>
#include <vector>

namespace astrodb {

class CameraTable;
class InfoSnippetTable;
class ObjectTable;
class ObserverTable;
class Plugin;
class TelescopeTable;

class Database
{
public:

  /**
   * @brief A small utility container to obtain information about loaded plugins.
   */
  struct PluginInfo
  {
    std::string name;
    std::string version;
    std::string filename;
  };

  Database() = default;
  virtual ~Database() = default;

  virtual void commit() = 0;

  virtual CameraTable* getCameraTable() = 0;

  virtual InfoSnippetTable* getInfoSnippetTable() = 0;

  virtual ObjectTable* getObjectTable() = 0;

  virtual ObserverTable* getObserverTable() = 0;

  virtual TelescopeTable* getTelescopeTable() = 0;

  static std::vector<std::string> getDrivers();

  static Database* connect(const std::string& driver, const std::string& db, const std::string& user, const std::string& passwd, const std::string& con="default");

  static Database* get(const std::string& con="default");

  /**
   * @brief Add a directory to the search path for plugins.
   *
   * @note Only directories added before the PuginManager object was
   *       created are considered.
   * @param path the directory to add
   */
  static void addSearchPath(const std::string& path);

  /**
   * @brief Name of the environment variable containing a list of directories to search for plugins.
   *
   * The environment variable contains a colon seperated list of directories,
   * which are searched for plugins in addition to the standard locations.
   */
  static const char* VAR_ASTRODB_PLUGIN_PATH;

private:

  class PluginHandler
  {
  public:
    /**
   * @brief Create a handler by loading a plugin from the given so-file.
   * @param name the filename
   */
    PluginHandler(const std::string& name);
    /**
   * @brief Create a handler from an existing plugin object.
   *
   * Note: The handler takes ownership of the object and deletes it in his
   *       destructor.
   * @param plugin the existing plugin object
   */
    PluginHandler(Plugin* plugin);
    PluginHandler(const PluginHandler&) = delete;
    ~PluginHandler();

    explicit operator bool() const noexcept  { return instance != nullptr; }

    std::string getFilename() const;

    std::string getPluginName() const;

    std::string getPluginVersion() const;

    std::vector<std::string> getDrivers() const;

    std::unique_ptr<Database> connect(const std::string& driver, const std::string& db, const std::string& user, const std::string& passwd);

    PluginHandler& operator=(const PluginHandler&) = delete;

  private:

    void* handle;
    std::string filename;
    Plugin* instance;

  };

  static void initialize();
  static void scan();
  static void scan(const std::string& dir);

  static std::map<std::string,std::unique_ptr<Database>> databases;
  static bool pluginsInititalized;
  static std::vector<std::unique_ptr<PluginHandler>> plugins;
  static bool envAdded;
  static std::vector<std::string> searchPath;

};

} // namespace astrodb

#endif // DATABASE_H
