#ifndef LED_MANAGER_H
#define LED_MANAGER_H

#include <Arduino.h>

class LedManager {
public:

  bool begin();

  void off();

  void red();

  void green();

  void blue();

  void yellow();

  void purple();

  void white();

  void bootAnimation();

  void sleep();
};

extern LedManager led;

#endif