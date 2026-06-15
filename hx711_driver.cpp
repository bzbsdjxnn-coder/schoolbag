
#include "hx711_driver.h"
#include "config.h"
#include "storage.h"

HX711Driver scale;

//-------------------------------------

bool HX711Driver::begin() {

  leftScale.begin(
    HX711_LEFT_DT,
    HX711_LEFT_SCK);

  rightScale.begin(
    HX711_RIGHT_DT,
    HX711_RIGHT_SCK);

  leftCalibration =
    storage.loadLeftCalibration();

  rightCalibration =
    storage.loadRightCalibration();

  leftScale.set_scale(
    leftCalibration);

  rightScale.set_scale(
    rightCalibration);

  leftScale.tare();

  rightScale.tare();

  leftWeight = 0;

  rightWeight = 0;

  totalWeight = 0;

  lastWeight = 0;

  stable = true;

  return true;
}

//-------------------------------------

void HX711Driver::update() {

  if (leftScale.is_ready()) {

    leftWeight =

      leftScale.get_units(5);
  }

  if (rightScale.is_ready()) {

    rightWeight =

      rightScale.get_units(5);
  }

  if (leftWeight < 0)
    leftWeight = 0;

  if (rightWeight < 0)
    rightWeight = 0;

  totalWeight =

    leftWeight +

    rightWeight;

  stable =

    abs(totalWeight - lastWeight)

    < 0.01;

  lastWeight =

    totalWeight;
}

//-------------------------------------

void HX711Driver::tare() {

  leftScale.tare();

  rightScale.tare();
}

//-------------------------------------

void HX711Driver::powerDown() {

  leftScale.power_down();

  rightScale.power_down();
}

//-------------------------------------

void HX711Driver::powerUp() {

  leftScale.power_up();

  rightScale.power_up();
}

//-------------------------------------

float HX711Driver::getLeftWeight() {

  return leftWeight;
}

//-------------------------------------

float HX711Driver::getRightWeight() {

  return rightWeight;
}

//-------------------------------------

float HX711Driver::getTotalWeight() {

  return totalWeight;
}

//-------------------------------------

bool HX711Driver::isStable() {

  return stable;
}

//------------------------------------

long HX711Driver::getLeftRaw() {

  if (!leftScale.is_ready())
    return 0;

  return leftScale.read();
}

//------------------------------------

long HX711Driver::getRightRaw() {

  if (!rightScale.is_ready())
    return 0;

  return rightScale.read();
}

//------------------------------------

void HX711Driver::setLeftCalibration(
  float factor) {

  leftCalibration = factor;

  leftScale.set_scale(
    leftCalibration);
}

//------------------------------------

void HX711Driver::setRightCalibration(
  float factor) {

  rightCalibration = factor;

  rightScale.set_scale(
    rightCalibration);
}

//------------------------------------

float HX711Driver::getLeftCalibration() {

  return leftCalibration;
}

//------------------------------------

float HX711Driver::getRightCalibration() {

  return rightCalibration;
}
