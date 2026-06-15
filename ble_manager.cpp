#include "ble_manager.h"
#include "config.h"

BLEManager ble;

//--------------------------------------------------
// Server Callbacks
//--------------------------------------------------

class ServerCallbacks : public NimBLEServerCallbacks {
  void onConnect(NimBLEServer *pServer) {
    ble.connected = true;

    Serial.println("BLE Client Connected");
  }

  void onDisconnect(NimBLEServer *pServer) {
    ble.connected = false;

    Serial.println("BLE Client Disconnected");

    NimBLEDevice::startAdvertising();
  }
};

//--------------------------------------------------
// Command Callbacks
//--------------------------------------------------

class CommandCallbacks : public NimBLECharacteristicCallbacks {
  void onWrite(NimBLECharacteristic *pCharacteristic) {

    String cmd =
      String(
        pCharacteristic->getValue().c_str());

    cmd.trim();

    Serial.print("BLE CMD : ");

    Serial.println(cmd);

    if (cmd == "tare") {

      Serial.println("TARE");

      // scale.tare();

    }

    else if (cmd == "sleep") {

      Serial.println("SLEEP");

      // power.sleep();

    }

    else if (cmd == "restart") {

      Serial.println("RESTART");

      ESP.restart();

    }

    else if (cmd == "calibrate") {

      Serial.println("CALIBRATE");
    }
  }
};

//--------------------------------------------------
// BLE Begin
//--------------------------------------------------

bool BLEManager::begin() {

  connected = false;

  Serial.println("BLE Name: SmartBag");

  NimBLEDevice::init("SmartBag");

  server =
    NimBLEDevice::createServer();

  server->setCallbacks(
    new ServerCallbacks());

  service =
    server->createService(
      SERVICE_UUID);

  weightChar =
    service->createCharacteristic(

      WEIGHT_UUID,

      NIMBLE_PROPERTY::READ |

        NIMBLE_PROPERTY::NOTIFY

    );

  batteryChar =
    service->createCharacteristic(

      BATTERY_UUID,

      NIMBLE_PROPERTY::READ |

        NIMBLE_PROPERTY::NOTIFY

    );

  infoChar =
    service->createCharacteristic(

      INFO_UUID,

      NIMBLE_PROPERTY::READ

    );

  commandChar =
    service->createCharacteristic(

      COMMAND_UUID,

      NIMBLE_PROPERTY::WRITE

    );

  commandChar->setCallbacks(
    new CommandCallbacks());

  updateInfo();

  service->start();

  NimBLEAdvertising *advertising =
    NimBLEDevice::getAdvertising();

  advertising->addServiceUUID(
    SERVICE_UUID);

  advertising->start();

  Serial.println("BLE Ready");

  return true;
}
//--------------------------------------------------
// Update Weight
//--------------------------------------------------

void BLEManager::updateWeight(float weight) {

  if (weightChar == nullptr)
    return;

  char buffer[16];

  snprintf(
    buffer,
    sizeof(buffer),
    "%.2f",
    weight);

  weightChar->setValue(buffer);

  if (connected) {
    weightChar->notify();
  }
}

//--------------------------------------------------
// Update Battery
//--------------------------------------------------

void BLEManager::updateBattery(uint8_t battery) {

  if (batteryChar == nullptr)
    return;

  char buffer[5];

  snprintf(
    buffer,
    sizeof(buffer),
    "%d",
    battery);

  batteryChar->setValue(buffer);

  if (connected) {
    batteryChar->notify();
  }
}

//--------------------------------------------------
// Update Device Information
//--------------------------------------------------

void BLEManager::updateInfo() {

  if (infoChar == nullptr)
    return;

  String json = "{";

  json += "\"fw\":\"";
  json += FW_VERSION;
  json += "\",";

  uint64_t chipId = ESP.getEfuseMac();

  char deviceId[20];

  sprintf(
    deviceId,
    "SB-%06X",
    (uint32_t)(chipId & 0xFFFFFF));

  json += "\"device\":\"";
  json += deviceId;
  json += "\",";

  json += "\"status\":\"READY\"";

  json += "}";

  infoChar->setValue(
    json.c_str());
}

//--------------------------------------------------
// Connection Status
//--------------------------------------------------

bool BLEManager::isConnected() const {
  return connected;
}
