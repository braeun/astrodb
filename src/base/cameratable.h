#ifndef ASTRODB_CAMERATABLE_H
#define ASTRODB_CAMERATABLE_H

#include "data/camera.h"
#include <string>
#include <vector>

namespace astrodb {

class CameraTable
{
public:
  CameraTable();
  virtual ~CameraTable() = default;

  virtual bool contains(const std::string& id) = 0;

  virtual std::vector<std::string> getIdList() = 0;

  virtual std::vector<Camera> getAll() = 0;

  virtual Camera get(const std::string& id) = 0;

  virtual bool add(const Camera& c) = 0;

  virtual bool update(const Camera& c) = 0;

  virtual bool remove(const std::string& id) = 0;

};

} // namespace astrodb

#endif // CAMERATABLE_H
