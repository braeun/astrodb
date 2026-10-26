#ifndef ASTRODB_CAMERATABLE_H
#define ASTRODB_CAMERATABLE_H

#include "data/camera.h"
#include <QString>
#include <vector>

namespace astrodb {

class CameraTable
{
public:
  CameraTable();
  virtual ~CameraTable() = default;

  virtual bool contains(const QString& name) = 0;

  virtual std::vector<QString> getNameList() = 0;

  virtual std::vector<Camera> getAll() = 0;

  virtual Camera get(const QString& name) = 0;

  virtual bool add(Camera c) = 0;

  virtual bool update(const Camera& c) = 0;

  virtual bool remove(const QString& name) = 0;

  virtual bool remove(int64_t id) = 0;

};

} // namespace astrodb

#endif // CAMERATABLE_H
