
#include "battery.h"
#include "config.h"

BatteryManager battery;

bool BatteryManager::begin()
{
    analogReadResolution(12);
    analogSetPinAttenuation(BATTERY_ADC, ADC_11db);

    voltage = 0.0f;
    percentage = 0;

    return true;
}

void BatteryManager::update()
{
    const uint8_t samples = 10;

    uint32_t sum = 0;

    for(uint8_t i = 0; i < samples; i++)
    {
        sum += analogRead(BATTERY_ADC);
    }

    float adc = (float)sum / samples;

    float adcVoltage =
        (adc * 3.3f) / 4095.0f;

    // 100K + 100K divider
    float newVoltage =
        adcVoltage * 2.0f;

    // Exponential smoothing
    voltage =
        (voltage * 0.8f) +
        (newVoltage * 0.2f);

    float percent =
        ((voltage - BATTERY_MIN) /
        (BATTERY_MAX - BATTERY_MIN))
        * 100.0f;

    if(percent > 100)
        percent = 100;

    if(percent < 0)
        percent = 0;

    percentage = (int)percent;
}

float BatteryManager::getVoltage()
{
    return voltage;
}

int BatteryManager::getPercentage()
{
    return percentage;
}

bool BatteryManager::isLowBattery()
{
    return voltage <= 3.40f;
}

