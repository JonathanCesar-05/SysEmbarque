#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Adafruit_BME280.h"

#define LIGHT_PIN        A0
#define TEMP_WATER_PIN   A1     // (module complémentaire : analogique)
#define PRESSURE_ADDR    0x76   // ex. BME280 sur I2C
#define GPS_SERIAL_RX    2      // mettre les broches que tu utilises
#define GPS_SERIAL_TX    3

// Capteurs principaux (exemple BME280)
Adafruit_BME280 bme(PRESSURE_ADDR);
// GPS via SoftwareSerial
SoftwareSerial gpsSerial(GPS_SERIAL_RX, GPS_SERIAL_TX);

typedef struct {
    int16_t temp;
    uint16_t atmo_press;
    int16_t alt;
    uint8_t humi;
    uint16_t light;
    char datetime[22];
    char gpsData[50];
} CapteurData;

void acquisition(CapteurData *data);
