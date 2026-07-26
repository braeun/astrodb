#ifndef ASTRODB_TELESCOPE_H
#define ASTRODB_TELESCOPE_H

#include <string>

namespace astrodb {

class Telescope
{
public:
  Telescope();
  Telescope(const std::string& model, double f, double d);

  const std::string& getModel() const;
  void setModel(const std::string& m);
  double getFocalLength() const;
  void setFocalLength(double f);
  double getAperture() const;
  void setAperture(double d);

  explicit operator bool() const;

private:
  std::string model;
  double focalLength;
  double aperture;
};

} // namespace astrodb

#endif // TELESCOPE_H
