#include "../lib/acquisition.h"
#include "../lib/clock.h" // Pour gestion du RTC
#include "../lib/gestionSD.h"

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

void acquisitionSansGPS(CapteurData *data) {
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

    strncpy(data->gpsData, "No GPS eco", sizeof(data->gpsData)-1);
    data->gpsData[sizeof(data->gpsData)-1] = '\0';
}

void afficherDonneesSerial(const CapteurData *data) {
    Serial.print("Date/heure : "); Serial.println(data->datetime);
    Serial.print("Température : "); Serial.print(data->temp/10.0); Serial.println(" °C");
    Serial.print("Pression : "); Serial.print(data->atmo_press); Serial.println(" hPa");
    Serial.print("Altitude : "); Serial.print(data->alt); Serial.println(" m");
    Serial.print("Humidité : "); Serial.print(data->humi); Serial.println(" %");
    Serial.print("Luminosité : "); Serial.print(data->light); Serial.println(" (ADC)");
    Serial.print("GPS : "); Serial.println(data->gpsData);
    Serial.println("--------------------------");
}

void enregistrerMesureSD(const CapteurData *data) {
    char ligneDonnees[128];
    snprintf(ligneDonnees, sizeof(ligneDonnees),
        "%s,%d,%d,%d,%d,%u,%s",
        data->datetime,
        data->temp,
        data->atmo_press,
        data->alt,
        data->humi,
        data->light,
        data->gpsData
    );
    // Puis tu appelles la fonction d’écriture SD :
    ecrireLigneDonnees(ligneDonnees);
}
