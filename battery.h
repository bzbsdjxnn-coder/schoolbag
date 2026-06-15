
#ifndef BATTERY_H
#define BATTERY_H

#include <Arduino.h>

class BatteryManager {
public:

  bool begin();

  void update();

  float getVoltage();

  int getPercentage();

  bool isLowBattery();

private:

  float voltage = 0.0f;

  int percentage = 0;
};

extern BatteryManager battery;

#endif
