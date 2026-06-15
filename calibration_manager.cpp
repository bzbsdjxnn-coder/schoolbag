
#include "calibration_manager.h"

#include "hx711_driver.h"
#include "storage.h"

CalibrationManager calibration;

//----------------------------------------

bool CalibrationManager::begin() {
  running = false;

  return true;
}

//----------------------------------------

void CalibrationManager::start(
  float knownWeight) {
  referenceWeight = knownWeight;

  running = true;

  scale.tare();
  Serial.println("---------------------");
  Serial.println("REMOVE ALL WEIGHT");
  Serial.println("TARE COMPLETE");
  Serial.println("PLACE KNOWN WEIGHT");
  Serial.println("---------------------");
  Serial.println("Calibration Started");

  Serial.println("Place Weight...");
}

//----------------------------------------

bool CalibrationManager::isRunning() {
  return running;
}

//----------------------------------------

bool CalibrationManager::process() {
  if (!running)
    return false;

  Serial.println("Waiting for stable reading...");

  while (!scale.isStable()) {
    scale.update();
    delay(20);
  }

  long leftRaw = scale.getLeftRaw();

  long rightRaw = scale.getRightRaw();

  if (leftRaw == 0 || rightRaw == 0) {
    Serial.println("Calibration Failed");

    running = false;

    return false;
  }

  float leftFactor =
    (float)leftRaw / referenceWeight;

  float rightFactor =
    (float)rightRaw / referenceWeight;

  scale.setLeftCalibration(leftFactor);

  scale.setRightCalibration(rightFactor);

  storage.saveLeftCalibration(leftFactor);

  storage.saveRightCalibration(rightFactor);

  Serial.println("Calibration Complete");

  Serial.print("Left Factor : ");
  Serial.println(leftFactor);

  Serial.print("Right Factor : ");
  Serial.println(rightFactor);

  running = false;

  return true;
}
