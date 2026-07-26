#ifndef ASTRODB_JSONOBSERVERTABLE_H
#define ASTRODB_JSONOBSERVERTABLE_H

#include "../observertable.h"
#include "json_fwd.hpp"
#include <map>

namespace astrodb {

class JsonObserverTable: public ObserverTable
{
public:
  JsonObserverTable();
  ~JsonObserverTable();

  virtual bool contains(const std::string& id) override;

  virtual std::vector<std::string> getIdList() override;

  virtual std::vector<Observer> getAll() override;

  virtual Observer get(const std::string& id) override;

  virtual bool add(const Observer& c) override;

  virtual bool update(const Observer& c) override;

  virtual bool remove(const std::string& id) override;

  bool load(const nlohmann::json& json);

  nlohmann::json save();

private:
  std::map<std::string,Observer> data;
};

} // namespace astrodb

#endif // JSONOBSERVERTABLE_H
