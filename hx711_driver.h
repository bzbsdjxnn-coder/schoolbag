
#ifndef HX711_DRIVER_H
#define HX711_DRIVER_H

#include <Arduino.h>
#include <HX711.h>

class HX711Driver {
public:

  bool begin();

  void update();

  void tare();

  void powerDown();

  void powerUp();

  float getLeftWeight();

  float getRightWeight();

  float getTotalWeight();

  long getLeftRaw();

  long getRightRaw();

  void setLeftCalibration(float factor);

  void setRightCalibration(float factor);

  float getLeftCalibration();

  float getRightCalibration();

  bool isStable();

private:

  HX711 leftScale;

  HX711 rightScale;

  float leftWeight;

  float rightWeight;

  float totalWeight;

  float leftCalibration;

  float rightCalibration;

  float lastWeight;

  bool stable;
};

extern HX711Driver scale;

#endif
