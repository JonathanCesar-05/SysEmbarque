#ifndef LED_MANAGER_H
#define LED_MANAGER_H

#include <Arduino.h>

enum SystemMode {
  MODE_STANDARD,
  MODE_CONFIGURATION,
  MODE_ECONOMIQUE,
  MODE_MAINTENANCE,
  MODE_ERROR
};

void initLED();
void setLEDColor(SystemMode mode);

#endif