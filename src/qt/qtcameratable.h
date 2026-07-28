#ifndef ASTRODB_QTCAMERATABLE_H
#define ASTRODB_QTCAMERATABLE_H

#include <base/cameratable.h>
#include <base/data/camera.h>
#include <QString>

namespace astrodb {

class QtCameraTable: public CameraTable
{
public:
  QtCameraTable(const QString& db);
  ~QtCameraTable();

  virtual bool contains(const std::string& id) override;

  virtual std::vector<std::string> getIdList() override;

  virtual std::vector<Camera> getAll() override;

  virtual Camera get(const std::string& id) override;

  virtual bool add(const Camera& c) override;

  virtual bool update(const Camera& c) override;

  virtual bool remove(const std::string& id) override;

private:
  void assertTable();

  QString db;
};

} // namespace astrodb

#endif // QTCAMERATABLE_H
