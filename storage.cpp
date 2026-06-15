#include "storage.h"
#include "config.h"
Storage storage;

//----------------------------------------

bool Storage::begin() {

  return prefs.begin(
    "smartbag",
    false);
}

//----------------------------------------

void Storage::end() {

  prefs.end();
}

//----------------------------------------

bool Storage::saveLeftCalibration(
  float value) {

  return prefs.putFloat(
           "leftCal",
           value)
         > 0;
}

//----------------------------------------

bool Storage::saveRightCalibration(
  float value) {

  return prefs.putFloat(
           "rightCal",
           value)
         > 0;
}

//----------------------------------------

float Storage::loadLeftCalibration() {

  return prefs.getFloat(
    "leftCal",
    420.0f);
}

//----------------------------------------

float Storage::loadRightCalibration() {

  return prefs.getFloat(
    "rightCal",
    420.0f);
}

//----------------------------------------

bool Storage::saveDeviceID(
  const String &id) {

  return prefs.putString(
           "deviceID",
           id)
         > 0;
}

//----------------------------------------

String Storage::loadDeviceID() {

  return prefs.getString(
    "deviceID",
    "SB001");
}

//----------------------------------------

bool Storage::saveFirmwareVersion(
  const String &version) {

  return prefs.putString(
           "fw",
           version)
         > 0;
}

//----------------------------------------

String Storage::loadFirmwareVersion() {

  return prefs.getString(
    "fw",
    FW_VERSION);
}
