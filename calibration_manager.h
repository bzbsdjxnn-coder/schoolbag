
#ifndef CALIBRATION_MANAGER_H
#define CALIBRATION_MANAGER_H

#include <Arduino.h>

class CalibrationManager {
public:

  bool begin();

  void start(float knownWeight);

  bool isRunning();

  bool process();

private:

  bool running = false;

  float referenceWeight = 0.0f;
};

extern CalibrationManager calibration;

#endif
