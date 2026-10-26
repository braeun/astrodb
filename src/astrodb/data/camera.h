#ifndef ASTRODB_CAMERA_H
#define ASTRODB_CAMERA_H

#include <cstdint>
#include <string>

namespace astrodb {

class Camera
{
public:
  Camera();
  Camera(const std::string& model, int width, int height, int64_t id=-1);

  int64_t getId() const;

  void setId(int64_t i);

  const std::string& getModel() const;

  void setModel(const std::string& newModel);

  int getWidth() const;

  void setWidth(int newWidth);

  int getHeight() const;

  void setHeight(int newHeight);

  double getPixelWidth() const;

  void setPixelWidth(double newPixelwidth);

  double getPixelHeight() const;

  void setPixelHeight(double newPixelheight);

  double getSensorWidth() const;

  void setSensorWidth(double newSensorwidth);

  double getSensorHeight() const;

  void setSensorHeight(double newSensorheight);

  int getBpp() const;

  void setBpp(int newBpp);

  explicit operator bool() const;

private:
  int64_t id;
  std::string model;
  int width; //!< in pixel
  int height; //!< in pixel
  double pixelwidth; //!< width of a pixel in m
  double pixelheight; //!< height of a pixel in m
  double sensorwidth; //!< width of the sensor in m
  double sensorheight; //!< height of the sensor in m
  int bpp;      //!< bit per pixel
};

} // namespace astrodb

#endif // ASTRODB_CAMERA_H
