#include "temperature.hpp"
#include "Config.h"
#include <Arduino.h>

void logic_setup() {
  pinMode(PIN_MIXER, OUTPUT);
  pinMode(PIN_HEATER, OUTPUT);
  pinMode(PIN_COOLER, OUTPUT);
}

void logic_on_temperature(float t) {

  return;
}
