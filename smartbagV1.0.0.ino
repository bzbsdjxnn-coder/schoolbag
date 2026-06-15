
/*
====================================================
SMART BAG FIRMWARE
Version 1.0.0
====================================================
*/

#include "config.h"

#include "battery.h"
#include "ble_manager.h"
#include "hx711_driver.h"
#include "led_manager.h"
#include "oled_manager.h"
#include "power_manager.h"
#include "scheduler.h"
#include "smartbag_data.h"
#include "storage.h"
#include "calibration_manager.h"

//----------------------------------------------------

unsigned long batteryTimer = 0;
unsigned long weightTimer = 0;
unsigned long bleTimer = 0;
unsigned long oledTimer = 0;

//----------------------------------------------------

void setup() {
  Serial.begin(115200);

  delay(500);
  
  Serial.println("================================");
  Serial.println("SMART BAG");
  Serial.print("Firmware : ");
  Serial.println(FW_VERSION);
  Serial.println("================================");

  storage.begin();

  battery.begin();

  power.begin();

  oled.begin();

  led.begin();

  scale.begin();

  ble.begin();

  calibration.begin();

  oled.bootScreen();

  led.bootAnimation();

  delay(1500);

  oled.showReady();

  led.green();

  Serial.println("System Ready");
}

//----------------------------------------------------

void loop() {
  //------------------------------------
  // Power Management
  //------------------------------------

  power.update();

  //------------------------------------
  // Battery Update
  //------------------------------------

  if (scheduler.every(1000, batteryTimer)) {
    battery.update();

    bagData.batteryVoltage =
      battery.getVoltage();

    bagData.batteryPercent =
      battery.getPercentage();

    bagData.lowBattery =
      battery.isLowBattery();
  }

  //------------------------------------
  // HX711 Update
  //------------------------------------

  if (scheduler.every(100, weightTimer)) {
    scale.update();

    bagData.leftWeight =
      scale.getLeftWeight();

    bagData.rightWeight =
      scale.getRightWeight();

    bagData.totalWeight =
      scale.getTotalWeight();

    bagData.stable =
      scale.isStable();

    if (bagData.totalWeight > 0.05) {
      power.resetTimer();
    }
  }

  //------------------------------------
  // Calibration
  //------------------------------------

  if (calibration.isRunning()) {
    calibration.process();
  }

  //------------------------------------
  // BLE Update
  //------------------------------------

  if (scheduler.every(250, bleTimer)) {
    bagData.bleConnected =
      ble.isConnected();

    ble.updateWeight(
      bagData.totalWeight);

    ble.updateBattery(
      bagData.batteryPercent);

    if (bagData.bleConnected) {
      power.resetTimer();
    }
  }

  //------------------------------------
  // OLED Update
  //------------------------------------

  if (scheduler.every(200, oledTimer)) {
    oled.showStatus(

      bagData.totalWeight,

      bagData.batteryPercent,

      bagData.bleConnected

    );
  }

  //------------------------------------
  // LED Status
  //------------------------------------

  if (bagData.lowBattery) {
    led.purple();
  } else if (bagData.totalWeight > 5.50f) {
    led.red();
  } else if (bagData.bleConnected) {
    led.yellow();
  } else {
    led.green();
  }

  //------------------------------------
  // Sleep Status
  //------------------------------------

  bagData.sleeping =
    power.isSleeping();

  delay(1);
}
