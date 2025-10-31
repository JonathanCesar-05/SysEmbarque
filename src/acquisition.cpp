#include "../lib/acquisition.h"
#include "../lib/clock.h" // Pour gestion du RTC

void acquisition(CapteurData *data) {
  // Acquire sensor data
  data->temp = (int16_t)(bme.readTemperature() * 10);
  data->atmo_press = (uint16_t)(bme.readPressure() / 100);
  data->alt = (int16_t)(bme.readAltitude(data->atmo_press));
  data->humi = (uint8_t)bme.readHumidity();
  data->light = analogRead(LIGHT_PIN);

  // Acquire date and time
  byte second, minute, hour, day, month, year;
  getDS1307Time(&second, &minute, &hour, &day, &month, &year);
  snprintf(data->datetime, sizeof(data->datetime), "20%02d/%02d/%02d %02d:%02d:%02d", year, month, day, hour, minute, second);

  if (gpsSerial.available()) {
        String gpsRaw = gpsSerial.readStringUntil('\n');
        strncpy(data->gpsData, gpsRaw.c_str(), sizeof(data->gpsData)-1);
        data->gpsData[sizeof(data->gpsData)-1] = '\0';
    } else {
        strncpy(data->gpsData, "No GPS data", sizeof(data->gpsData)-1);
        data->gpsData[sizeof(data->gpsData)-1] = '\0';
    }
}
