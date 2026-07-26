#ifndef ASTRODB_JSONOBJECTTABLE_H
#define ASTRODB_JSONOBJECTTABLE_H

#include "../objecttable.h"
#include "json_fwd.hpp"
#include <map>

namespace astrodb {

class JsonObjectTable: public ObjectTable
{
public:
  JsonObjectTable();
  ~JsonObjectTable();

  virtual bool contains(const std::string& id) override;

  virtual std::vector<std::string> getIdList() override;

  virtual std::vector<Object> getAll() override;

  virtual Object get(const std::string& id) override;

  virtual bool add(const Object& c) override;

  virtual bool update(const Object& c) override;

  virtual bool remove(const std::string& id) override;

  bool load(const nlohmann::json& json);

  nlohmann::json save();

private:
  std::map<std::string,Object> data;
};

} // namespace astrodb

#endif // JSONOBJECTTABLE_H
