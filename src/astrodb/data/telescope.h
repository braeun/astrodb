#ifndef ASTRODB_TELESCOPE_H
#define ASTRODB_TELESCOPE_H

#include <cstdint>
#include <string>

namespace astrodb {

/**
 * @brief The Telescope class contains the relevant telescope data.
 *
 * All values with units like focal length etc. are in SI base units.
 */
class Telescope
{
public:
  Telescope();
  Telescope(const std::string& model, double f, double d, int64_t id=-1);

  int64_t getId() const;

  void setId(int64_t i);

  const std::string& getModel() const;

  void setModel(const std::string& m);

  /**
   * @brief Get the focal length of the telescope.
   * @return focal length in m
   */
  double getFocalLength() const;

  void setFocalLength(double f);

  double getAperture() const;

  void setAperture(double d);

  explicit operator bool() const;

private:
  int64_t id;
  std::string model;
  double focalLength;
  double aperture;
};

} // namespace astrodb

#endif // TELESCOPE_H
