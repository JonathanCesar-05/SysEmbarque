#include "../lib/config.h"
#include "../lib/gestionLed.h"
#include "../lib/clock.h"

void reset_parameters(config_s cfg) {
  cfg.LOG_INTERVAL = 600000;
  cfg.FILE_MAX_SIZE = 4096;
  cfg.TIMEOUT = 30;
  cfg.LUMIN = 1;
  cfg.LUMIN_LOW = 255;
  cfg.LUMIN_HIGH = 768;
  cfg.TEMP_AIR = 1;
  cfg.MIN_TEMP_AIR = -10;
  cfg.MAX_TEMP_AIR = 60;
  cfg.HYGR = 1;
  cfg.HYGR_MINT = 0;
  cfg.HYGR_MAXT = 50;
  cfg.PRESSURE = 1;
  cfg.PRESSURE_MIN = 850;
  cfg.PRESSURE_MAX = 1030;
}

void config() {
  Serial.println("Mode Configuration");
  couleurLed(MODE_CONFIGURATION);
  lastActivity = millis();
  while (millis() - lastActivity < CONFIG_TIMEOUT_MS) {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        SerialInput(input, cfg);
        lastActivity = millis();
    }
  }
}

void SerialInput(String input, config_s cfg) {
  input.trim(); // Remove spaces or backline
  if (input.startsWith("LOG_INTERVAL=")) {
    cfg.LOG_INTERVAL = input.substring(13).toInt();
    Serial.println(cfg.LOG_INTERVAL);
  } 
  else if (input.startsWith("FILE_MAX_SIZE=")) {
    cfg.FILE_MAX_SIZE = input.substring(14).toInt();
    Serial.println(cfg.FILE_MAX_SIZE);
  } 
  else if (input == "RESET") {
    reset_parameters(cfg);
  } 
  else if (input == "VERSION") {
    Serial.println(F("Version du programme : X.X, Lot : XXXXX"));
  } 
  else if (input.startsWith("TIMEOUT=")) {
    cfg.TIMEOUT = input.substring(8).toInt();
    Serial.println(cfg.TIMEOUT);
  } 
  else if (input.startsWith("LUMIN=")) {
    cfg.LUMIN = input.substring(6).toInt();
    Serial.println(cfg.LUMIN);
  } 
  else if (input.startsWith("TEMP_AIR=")) {
    cfg.TEMP_AIR = input.substring(9).toInt();
    Serial.println(cfg.TEMP_AIR);
  } 
  else if (input.startsWith("HYGR=")) {
    cfg.HYGR = input.substring(5).toInt();
    Serial.println(cfg.HYGR);
  } 
  else if (input.startsWith("PRESSURE=")) {
    cfg.PRESSURE = input.substring(9).toInt();
    Serial.println(cfg.PRESSURE);
  } 
  else if (input.startsWith("CLOCK=")) {
    String timeString = input.substring(6);
    int h = timeString.substring(0,2).toInt();
    int m = timeString.substring(3,5).toInt();
    int s = timeString.substring(6,10).toInt();
    setHeureRTC(h, m, s);
    Serial.print(F("Heure RTC réglée : "));
    Serial.print(h); Serial.print(":"); Serial.print(m); Serial.print(":"); Serial.println(s);
  }
  else if (input.startsWith("DATE=")) {
    String dateString = input.substring(5);
    int d = dateString.substring(0,2).toInt();
    int m = dateString.substring(3,5).toInt();
    int y = dateString.substring(6,10).toInt();
    setDateRTC(d, m, y);
    Serial.print(F("Date RTC réglée : "));
    Serial.print(d); Serial.print("/"); Serial.print(m); Serial.print("/"); Serial.println(y);
  }
}

