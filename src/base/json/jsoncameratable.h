#ifndef ASTRODB_JSONCAMERATABLE_H
#define ASTRODB_JSONCAMERATABLE_H

#include "../cameratable.h"
#include "../data/camera.h"
#include "json_fwd.hpp"
#include <map>
#include <vector>

namespace astrodb {

class JsonCameraTable: public CameraTable
{
public:
  JsonCameraTable();
  ~JsonCameraTable();

  virtual bool contains(const std::string& id) override;

  virtual std::vector<std::string> getIdList() override;

  virtual std::vector<Camera> getAll() override;

  virtual Camera get(const std::string& id) override;

  virtual bool add(const Camera& c) override;

  virtual bool update(const Camera& c) override;

  virtual bool remove(const std::string& id) override;

  bool load(const nlohmann::json& json);

  nlohmann::json save();

private:
  std::map<std::string,Camera> data;
};

} // namespace astrodb

#endif // JSONCAMERATABLE_H
