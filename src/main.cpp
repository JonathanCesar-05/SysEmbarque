#include "../lib/gestionLed.h"
#include "../lib/config.h"
#include "../lib/gestionSD.h"
#include "../lib/gestionErreur.h"

#include <Arduino.h>
#include "DS1307.h"

// Déclaration des objets et prototypes
extern void couleurLed(uint8_t modeActuel);
extern void initclock();
extern void printTime();
extern void modeConfiguration();

void setup() {
  Serial.begin(9600);

  initialisation_led();
  couleurLed(MODE_STANDARD);
  
  // initgestionmodes
  initclock();
  
}

void loop() {

  if (erreurActive()) {
    gererClignotementErreur();
    delay(10);
    return;  // Ne fait rien d'autre si erreur active
  }

  //uint8_t modeActuel = getModeActuel();
    
  switch (modeActuel) {
    case MODE_STANDARD:
    case MODE_ECONOMIQUE:
      //executerAcquisitionPeriodique();
      break;
            
    case MODE_MAINTENANCE:
      // executerModeMaintenance();
      break;
            
      case MODE_CONFIGURATION:
      // executerModeConfiguration();
            break;
    }
}

