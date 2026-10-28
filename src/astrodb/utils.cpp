#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <filesystem>
#include <string>
#include <vector>
#include <sstream>

namespace astrodb {

namespace utils {

std::string getHomePath()
{
  struct passwd *pw = getpwuid(getuid());
  return pw->pw_dir;
}

std::string getUserDataPath()
{
  std::filesystem::path p(getHomePath());
  p /= ".local";
  p /= "share";
  p /= "astrodb";
  if (!std::filesystem::exists(p))
  {
    std::filesystem::create_directories(p);
  }
  return p.string();
}

std::vector<std::string> split(const std::string& s, char delim, bool skipempty)
{
  std::vector<std::string> list;
  std::istringstream iss(s);
  std::string item;
  while (std::getline(iss,item,delim))
  {
    if (!(item.empty() && skipempty)) list.push_back(item);
  }
  return list;
}


}

} // namespace astrodb


