#ifndef GESTION_LED_H
#define GESTION_LED_H

#include <cstdint>
// ajouter librairie chainableLED

enum mode {
    MODE_STANDARD,
    MODE_ECONOMIQUE,
    MODE_CONFIGURATION,
    MODE_MAINTENANCE
};

enum erreur {
    ERREUR_RTC,
    ERREUR_GPS,
    ERREUR_DONNEES_CAPTEUR,
    ERREUR_DONNEES_INCOHERENTE,
    ERREUR_SD_PLEINE,
    ERREUR_ECRITURE_SD
};

void initialisation_led();
void allumerCouleur(uint8_t rouge, uint8_t vert, uint8_t bleu);
void couleurLed(uint8_t modeActuel);
void blinkLedWithCoef(uint8_t ledIndex, uint8_t r, uint8_t g, uint8_t b, int delayTime, uint8_t coef);
void erreurLed(uint8_t nErreur);

extern ChainableLED led;
extern int delayTime;

#endif