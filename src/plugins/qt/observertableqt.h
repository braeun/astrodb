#ifndef OBSERVERTABLEQT_H
#define OBSERVERTABLEQT_H

#include <astrodb/observertable.h>
#include <QString>

class QSqlQuery;

namespace astrodb {

class ObserverTableQt: public ObserverTable
{
public:
  ObserverTableQt(const QString& con);
  ~ObserverTableQt() = default;

  virtual bool contains(const std::string& id) override;

  virtual std::vector<std::string> getNameList() override;

  virtual std::vector<Observer> getAll() override;

  virtual Observer get(const std::string& id) override;

  virtual bool add(Observer c) override;

  virtual bool update(const Observer& c) override;

  virtual bool remove(const std::string& id) override;

  virtual bool remove(int64_t id) override;

private:
  Observer get(const QSqlQuery& q) const;

  QString con;
  QString lastError;
};

} // namespace astrodb

#endif // OBSERVERTABLEQT_H
