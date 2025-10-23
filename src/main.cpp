#include <Arduino.h>
#include "../lib/gestionLed.h"
#include "../lib/config.h"
#include "DS1307.h"

// Déclaration des objets et prototypes
extern void couleurLed(uint8_t modeActuel);
extern void initclock();
extern void printTime();
extern void modeConfiguration();

void setup() {
  Serial.begin(9600);
  // Initialisation de l’horloge RTC
  initclock();
  // Affichage de l’heure au démarrage
  printTime();
  // Initialisation du mode LED standard
  couleurLed(MODE_STANDARD);
  // Passage en mode configuration pour test
  modeConfiguration();
}

void loop() {
  // Clignotement simple de la LED en mode maintenance
  couleurLed(MODE_MAINTENANCE);
  delay(1000);

  // Affichage régulier de l’heure
  printTime();
  delay(2000);

  // Passage en mode économique
  couleurLed(MODE_ECONOMIQUE);
  delay(1000);
}

