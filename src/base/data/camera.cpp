#include "camera.h"

namespace astrodb {

Camera::Camera():
  model(""),
  width(0),
  height(0),
  pixelwidth(0),
  pixelheight(0),
  sensorwidth(0),
  sensorheight(0),
  bpp(8)
{

}

Camera::Camera(const std::string& model, int width, int height):
  model(model),
  width(width),
  height(height),
  pixelwidth(0),
  pixelheight(0),
  sensorwidth(0),
  sensorheight(0),
  bpp(8)
{
}

const std::string& Camera::getModel() const
{
  return model;
}

void Camera::setModel(const std::string& newModel)
{
  model = newModel;
}

int Camera::getWidth() const
{
  return width;
}

void Camera::setWidth(int newWidth)
{
  width = newWidth;
}

int Camera::getHeight() const
{
  return height;
}

void Camera::setHeight(int newHeight)
{
  height = newHeight;
}

double Camera::getPixelWidth() const
{
  return pixelwidth;
}

void Camera::setPixelWidth(double newPixelwidth)
{
  pixelwidth = newPixelwidth;
}

double Camera::getPixelHeight() const
{
  return pixelheight;
}

void Camera::setPixelHeight(double newPixelheight)
{
  pixelheight = newPixelheight;
}

double Camera::getSensorWidth() const
{
  return sensorwidth;
}

void Camera::setSensorWidth(double newSensorwidth)
{
  sensorwidth = newSensorwidth;
}

double Camera::getSensorHeight() const
{
  return sensorheight;
}

void Camera::setSensorHeight(double newSensorheight)
{
  sensorheight = newSensorheight;
}

int Camera::getBpp() const
{
  return bpp;
}

void Camera::setBpp(int newBpp)
{
  bpp = newBpp;
}

Camera::operator bool() const
{
  return !model.empty(); // && width > 0 && height > 0;
}

} // namespace astrodb
