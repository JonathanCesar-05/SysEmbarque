#include <SoftwareSerial.h>
#include <Arduino.h>

typedef struct config_s {
  int LOG_INTERVAL = 600000;
  int FILE_MAX_SIZE = 4096;
  int TIMEOUT = 30;
  int LUMIN = 1;
  int LUMIN_LOW = 255;
  int LUMIN_HIGH = 768;
  int TEMP_AIR = 1;
  int MIN_TEMP_AIR = -10;
  int MAX_TEMP_AIR = 60;
  int HYGR = 1;
  int HYGR_MINT = 0;
  int HYGR_MAXT = 50;
  int PRESSURE = 1;
  int PRESSURE_MIN = 850;
  int PRESSURE_MAX = 1030;
} config_t;

config_t cfg;

unsigned long lastActivity = 0;
const unsigned long CONFIG_TIMEOUT_MS = 1800000; // 30 minutes

void reset_parameters(config_s cfg);
void serial_input(String input, config_s cfg);