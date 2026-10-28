#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace astrodb {

namespace utils {

extern std::string getHomePath();

extern std::string getUserDataPath();

extern std::vector<std::string> split(const std::string& s, char delim, bool skipempty);

}

} // namespace astrodb

#endif // UTILS_H
