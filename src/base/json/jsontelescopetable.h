#ifndef ASTRODB_JSONTELECOPETABLE_H
#define ASTRODB_JSONTELECOPETABLE_H

#include "../telescopetable.h"
#include "json_fwd.hpp"
#include <map>

namespace astrodb {

class JsonTelescopeTable: public TelescopeTable
{
public:
  JsonTelescopeTable();
  ~JsonTelescopeTable();

  virtual bool contains(const std::string& id) override;

  virtual std::vector<std::string> getIdList() override;

  virtual std::vector<Telescope> getAll() override;

  virtual Telescope get(const std::string& id) override;

  virtual bool add(const Telescope& c) override;

  virtual bool update(const Telescope& c) override;

  virtual bool remove(const std::string& id) override;

  bool load(const nlohmann::json& json);

  nlohmann::json save();

private:
  std::map<std::string,Telescope> data;
};

} // namespace astrodb

#endif // JSONTELECOPETABLE_H
