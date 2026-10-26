#ifndef ASTRODB_TELESCOPETABLE_H
#define ASTRODB_TELESCOPETABLE_H

#include "data/telescope.h"
#include <QString>
#include <vector>

namespace astrodb {

class TelescopeTable
{
public:
  TelescopeTable();
  virtual ~TelescopeTable() = default;

  virtual bool contains(const QString& id) = 0;

  virtual std::vector<QString> getNameList() = 0;

  virtual std::vector<Telescope> getAll() = 0;

  virtual Telescope get(const QString& id) = 0;

  virtual bool add(Telescope c) = 0;

  virtual bool update(const Telescope& c) = 0;

  virtual bool remove(const QString& id) = 0;

  virtual bool remove(int64_t id) = 0;

};

} // namespace astrodb

#endif // TELESCOPETABLE_H
