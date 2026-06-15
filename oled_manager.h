
#ifndef OLED_MANAGER_H
#define OLED_MANAGER_H

#include <Arduino.h>

class OLEDManager {
public:

  bool begin();

  void bootScreen();

  void showReady();

  void showStatus(
    float weight,
    int battery,
    bool ble);

  void showSleep();

  void showError(
    String msg);

private:

  float lastWeight;

  int lastBattery;

  bool lastBLE;
};

extern OLEDManager oled;

#endif
