#ifndef CAMERATABLEQT6_H
#define CAMERATABLEQT6_H

#include <astrodb/cameratable.h>
#include <QString>

class QSqlQuery;

namespace astrodb {

class CameraTableQt: public CameraTable
{
public:
  CameraTableQt(const QString& con);
  virtual ~CameraTableQt() = default;

  bool contains(const std::string& name) override;

  std::vector<std::string> getNameList() override;

  std::vector<Camera> getAll() override;

  Camera get(const std::string& name) override;

  bool add(Camera c) override;

  bool update(const Camera& c) override;

  bool remove(const std::string& name) override;

  bool remove(int64_t id) override;

private:
  Camera get(const QSqlQuery& q) const;

  QString con;
  QString lastError;
};

} // namespace astrodb

#endif // CAMERATABLEQT6_H
