#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>
#include <Preferences.h>

class Storage {
public:

  bool begin();

  void end();

  bool saveLeftCalibration(float value);

  bool saveRightCalibration(float value);

  float loadLeftCalibration();

  float loadRightCalibration();

  bool saveDeviceID(const String &id);

  String loadDeviceID();

  bool saveFirmwareVersion(const String &version);

  String loadFirmwareVersion();

private:

  Preferences prefs;
};

extern Storage storage;

#endif