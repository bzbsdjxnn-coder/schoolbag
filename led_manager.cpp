
#include "led_manager.h"

#include "config.h"

#include <FastLED.h>

CRGB leds[NUM_LEDS];

LedManager led;

//---------------------------------------

bool LedManager::begin() {

  FastLED.addLeds<
    WS2812B,
    LED_PIN,
    GRB >(leds, NUM_LEDS);

  FastLED.clear();

  FastLED.show();

  return true;
}

//---------------------------------------

void LedManager::off() {

  leds[0] = CRGB::Black;

  FastLED.show();
}

//---------------------------------------

void LedManager::red() {

  leds[0] = CRGB::Red;

  FastLED.show();
}

//---------------------------------------

void LedManager::green() {

  leds[0] = CRGB::Green;

  FastLED.show();
}

//---------------------------------------

void LedManager::blue() {

  leds[0] = CRGB::Blue;

  FastLED.show();
}

//---------------------------------------

void LedManager::yellow() {

  leds[0] = CRGB::Yellow;

  FastLED.show();
}

//---------------------------------------

void LedManager::purple() {

  leds[0] = CRGB::Purple;

  FastLED.show();
}

//---------------------------------------

void LedManager::white() {

  leds[0] = CRGB::White;

  FastLED.show();
}

//---------------------------------------

void LedManager::sleep() {

  leds[0] = CRGB(2, 2, 2);

  FastLED.show();
}

//---------------------------------------

void LedManager::bootAnimation() {

  blue();

  delay(150);

  green();

  delay(150);

  yellow();

  delay(150);

  purple();

  delay(150);

  white();

  delay(150);

  off();
}
