#include <stdio.h>
#include "../lib/gestionLed.h"
#include "../lib/config.h"

int modes[2] = {0,0}; //Tableau {cur mode, prev mode}, 0 = standard, 1 = eco, 2 = maintenace

void led_eco() {
    couleurLed(MODE_ECONOMIQUE);
}

void led_standard() {
    couleurLed(MODE_STANDARD);
}

void led_config() {
    couleurLed(MODE_CONFIGURATION);
}

void led_maintenance() {
    couleurLed(MODE_MAINTENANCE);
}

void eco(int *mode) {
    if (mode[0] == 0) {
        Serial.println(F("Mode Economique"));
        mode[1] = mode[0];
        mode[0] = 1;
        led_eco();
    } else if (mode[0] == 1) {
        Serial.println(F("Mode Standard"));
        mode[1] = mode[0];
        mode[0] = 0;
        led_standard();
    }
}

