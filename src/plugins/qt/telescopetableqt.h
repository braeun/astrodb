#ifndef TELESCOPETABLEQT_H
#define TELESCOPETABLEQT_H

#include <astrodb/telescopetable.h>
#include <QString>

class QSqlQuery;

namespace astrodb {

class TelescopeTableQt: public TelescopeTable
{
public:
  TelescopeTableQt(const QString& con);
  virtual ~TelescopeTableQt() = default;

  virtual bool contains(const std::string& id) override;

  virtual std::vector<std::string> getNameList() override;

  virtual std::vector<Telescope> getAll() override;

  virtual Telescope get(const std::string& id) override;

  virtual bool add(Telescope c) override;

  virtual bool update(const Telescope& c) override;

  virtual bool remove(const std::string& id) override;

  virtual bool remove(int64_t id) override;

private:
  Telescope get(const QSqlQuery& q) const;

  QString con;
  QString lastError;
};

} // namespace astrodb

#endif // TELESCOPETABLEQT_H
