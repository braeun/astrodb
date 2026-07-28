#ifndef ASTRODB_QTDATABASE_H
#define ASTRODB_QTDATABASE_H

#include <base/database.h>
#include <QString>

namespace astrodb {

class QtDatabase: public Database
{
public:
  QtDatabase(const QString& host, const QString& user, const QString& password, const QString& driver, const QString& database="astro");
};

}

#endif // QTDATABASE_H
