
#ifndef POWER_MANAGER_H
#define POWER_MANAGER_H

#include <Arduino.h>

class PowerManager {
public:

  bool begin();

  void update();

  void resetTimer();

  void sleepNow();

  bool isSleeping();

private:

  unsigned long lastActivity;

  bool sleeping;
};

extern PowerManager power;

#endif
