#ifndef GESTION_LED_H
#define GESTION_LED_H

#include <Arduino.h>
#include <ChainableLED.h>


enum mode {
    MODE_STANDARD,
    MODE_ECONOMIQUE,
    MODE_CONFIGURATION,
    MODE_MAINTENANCE
};


// Initialise la LED chainable
void initialisation_led();

// Allume la LED avec une couleur RGB spécifique
void allumerCouleur(uint8_t rouge, uint8_t vert, uint8_t bleu);

// Éteint la LED
void eteindreLed();

// Change la couleur selon le mode actuel
void couleurLed(uint8_t modeActuel);

// Variable globale externe (déclarée dans gestionLed.cpp)
extern ChainableLED led;

#endif
