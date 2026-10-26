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

  virtual bool contains(const std::string& name) = 0;

  virtual std::vector<std::string> getNameList() = 0;

  virtual std::vector<Camera> getAll() = 0;

  virtual Camera get(const std::string& name) = 0;

  virtual bool add(Camera c) = 0;

  virtual bool update(const Camera& c) = 0;

  virtual bool remove(const std::string& name) = 0;

  virtual bool remove(int64_t id) = 0;

};

} // namespace astrodb

#endif // CAMERATABLE_H
