
#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

#include <Arduino.h>
#include <NimBLEDevice.h>

class ServerCallbacks;

class BLEManager
{
public:

    bool begin();

    void updateWeight(float weight);

    void updateBattery(uint8_t battery);

    void updateInfo();

    bool isConnected() const;

private:

    friend class ServerCallbacks;

    bool connected = false;

    NimBLEServer* server = nullptr;

    NimBLEService* service = nullptr;

    NimBLECharacteristic* weightChar = nullptr;

    NimBLECharacteristic* batteryChar = nullptr;

    NimBLECharacteristic* infoChar = nullptr;

    NimBLECharacteristic* commandChar = nullptr;

};

extern BLEManager ble;

#endif
