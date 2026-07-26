#include "sqlite3database.h"
#include <stdexcept>

namespace astrodb {

Sqlite3Database::Sqlite3Database(const std::string& filename)
{
  int ret = sqlite3_open(filename.c_str(),&db);
  if (ret != SQLITE_OK)
  {
    std::string err = sqlite3_errmsg(db);
    sqlite3_close(db);
    throw std::runtime_error(err);
  }
}

Sqlite3Database::~Sqlite3Database()
{
  if (db)
  {
    sqlite3_close(db);
  }
}

} // namespace astrodb
