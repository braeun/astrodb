#include "telescope.h"

namespace astrodb {

Telescope::Telescope():
  id(-1),
  focalLength(0),
  aperture(0)
{
}

Telescope::Telescope(const std::string& model, double f, double d, int64_t id):
  id(id),
  model(model),
  focalLength(f),
  aperture(d)
{
}

int64_t Telescope::getId() const
{
  return id;
}

void Telescope::setId(int64_t i)
{
  id = i;
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
