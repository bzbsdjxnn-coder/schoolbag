
#include "power_manager.h"

#include "config.h"

#include <esp_sleep.h>

PowerManager power;

//----------------------------------------

bool PowerManager::begin() {

  pinMode(
    WAKE_BUTTON,
    INPUT_PULLUP);

  lastActivity = millis();

  sleeping = false;

  return true;
}

//----------------------------------------

void PowerManager::resetTimer() {

  lastActivity = millis();
}

//----------------------------------------

bool PowerManager::isSleeping() {

  return sleeping;
}

//----------------------------------------

void PowerManager::update() {

  if (sleeping)
    return;

  if (

    millis() - lastActivity >

    AUTO_SLEEP_TIME

  )

  {

    sleepNow();
  }
}

//----------------------------------------

void PowerManager::sleepNow() {

  sleeping = true;

  Serial.println();

  Serial.println("Preparing Sleep");

  delay(100);

  // Future:
  // oled.sleep();
  // scale.powerDown();
  // led.off();

  esp_sleep_enable_gpio_wakeup();

  gpio_wakeup_enable(
    (gpio_num_t)WAKE_BUTTON,
    GPIO_INTR_LOW_LEVEL);

  Serial.println("Deep Sleep");

  delay(100);

  esp_deep_sleep_start();
}
