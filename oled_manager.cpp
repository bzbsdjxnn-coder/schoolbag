
#include "oled_manager.h"

#include "config.h"

#include <Wire.h>

#include <Adafruit_GFX.h>

#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(

  SCREEN_WIDTH,

  SCREEN_HEIGHT,

  &Wire,

  -1

);

OLEDManager oled;

//--------------------------------------

bool OLEDManager::begin() {

  Wire.begin(

    OLED_SDA,

    OLED_SCL

  );

  if (

    !display.begin(

      SSD1306_SWITCHCAPVCC,

      OLED_ADDRESS

      )

  )

  {

    return false;
  }

  display.clearDisplay();

  display.display();

  lastWeight = -999;

  lastBattery = -1;

  lastBLE = false;

  return true;
}

//--------------------------------------

void OLEDManager::bootScreen() {

  display.clearDisplay();

  display.setTextSize(2);

  display.setTextColor(

    SSD1306_WHITE

  );

  display.setCursor(10, 0);

  display.println("SMART");

  display.setCursor(25, 16);

  display.println("BAG");

  display.display();
}

//--------------------------------------

void OLEDManager::showReady() {

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(20, 10);

  display.println("READY");

  display.display();
}

//--------------------------------------

void OLEDManager::showStatus(

  float weight,

  int battery,

  bool ble

)

{

  if (

    abs(weight - lastWeight) < 0.01 &&

    battery == lastBattery &&

    ble == lastBLE

  )

  {

    return;
  }

  lastWeight = weight;

  lastBattery = battery;

  lastBLE = ble;

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0, 0);

  display.print("Weight");

  display.setCursor(70, 0);

  display.print(battery);

  display.print("%");

  display.setTextSize(2);

  display.setCursor(0, 14);

  display.print(weight, 2);

  display.print("kg");

  display.setTextSize(1);

  display.setCursor(90, 20);

  if (ble) {

    display.print("BLE");

  } else {

    display.print("---");
  }

  display.display();
}

//--------------------------------------

void OLEDManager::showSleep() {

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(30, 12);

  display.println("Sleeping");

  display.display();
}

//--------------------------------------

void OLEDManager::showError(

  String msg

)

{

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0, 0);

  display.println("ERROR");

  display.setCursor(0, 16);

  display.println(msg);

  display.display();
}
