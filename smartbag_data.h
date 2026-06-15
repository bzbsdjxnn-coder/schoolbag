#ifndef SMARTBAG_DATA_H
#define SMARTBAG_DATA_H

#include <Arduino.h>

struct SmartBagData
{
    float leftWeight = 0.0;

    float rightWeight = 0.0;

    float totalWeight = 0.0;

    float batteryVoltage = 0.0;

    uint8_t batteryPercent = 0;

    bool bleConnected = false;

    bool stable = false;

    bool lowBattery = false;

    bool sleeping = false;
};

extern SmartBagData bagData;

#endif