#include "telescope.h"

namespace astrodb {

Telescope::Telescope() {}

Telescope::Telescope(const std::string& model, double f, double d):
  model(model),
  focalLength(f),
  aperture(d)
{
}

const std::string& Telescope::getModel() const
{
  return model;
}

void Telescope::setModel(const std::string& m)
{
  model = m;
}

double Telescope::getFocalLength() const
{
  return focalLength;
}

void Telescope::setFocalLength(double f)
{
  focalLength = f;
}

double Telescope::getAperture() const
{
  return aperture;
}

void Telescope::setAperture(double a)
{
  aperture = a;
}

Telescope::operator bool() const
{
  return !model.empty();
}



} // namespace astrodb
