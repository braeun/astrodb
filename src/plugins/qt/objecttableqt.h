#ifndef OBJECTTABLEQT_H
#define OBJECTTABLEQT_H

#include <astrodb/objecttable.h>
#include <QString>

class QSqlQuery;

namespace astrodb {

class ObjectTableQt: public ObjectTable
{
public:
  ObjectTableQt(const QString& con);
  virtual ~ObjectTableQt() = default;

  virtual bool contains(const std::string& id) override;

  virtual std::vector<std::string> getNameList() override;

  virtual std::vector<Object> getAll() override;

  virtual Object get(const std::string& id) override;

  virtual bool add(Object c) override;

  virtual bool update(const Object& c) override;

  virtual bool remove(const std::string& id) override;

  virtual bool remove(int64_t id) override;

private:
  Object get(const QSqlQuery& q) const;

  QString con;
  QString lastError;
};

} // namespace astrodb

#endif // OBJECTTABLEQT_H
