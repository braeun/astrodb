#ifndef MEMORYCAMERATABLE_H
#define MEMORYCAMERATABLE_H

#include "../cameratable.h"
#include "../data/camera.h"
#include <map>
#include <vector>

namespace astrodb {

class MemoryCameraTable: public CameraTable
{
public:
  MemoryCameraTable();
  ~MemoryCameraTable();

  virtual bool contains(const std::string& name) override;

  virtual std::vector<std::string> getNameList() override;

  virtual std::vector<Camera> getAll() override;

  virtual Camera get(const std::string& name) override;

  virtual bool add(Camera c) override;

  virtual bool update(const Camera& c) override;

  virtual bool remove(const std::string& name) override;

  virtual bool remove(int64_t id) override;

private:
  int64_t id;
  std::map<std::string,Camera> data;

};

} // namespace astrodb

#endif // MEMORYCAMERATABLE_H
