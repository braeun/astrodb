#ifndef ASTRODB_SQLITE3DATABASE_H
#define ASTRODB_SQLITE3DATABASE_H

#include "../database.h"
#include <sqlite3.h>
#include <string>

namespace astrodb {

class Sqlite3Database: public Database
{
public:
  Sqlite3Database(const std::string& filename);
  ~Sqlite3Database();

private:
  sqlite3* db;
};

} // namespace astrodb

#endif // SQLITE3DATABASE_H
