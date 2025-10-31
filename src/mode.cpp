#include "../lib/gestionLed.h"
#include "../lib/mode.h"

void isrVert() {
  if (digitalRead(BTN_VERT) == LOW) {
    tpsAppuiVert = millis();
    appuiVertEnCours = true;
    changementFaitVert = false;
  } else {
    appuiVertEnCours = false;
    changementFaitVert = false;
  }
}

void isrRouge() {
  if (digitalRead(BTN_ROUGE) == LOW) {
    tpsAppuiRouge = millis();
    appuiRougeEnCours = true;
    changementFaitRouge = false;
  } else {
    appuiRougeEnCours = false;
    changementFaitRouge = false;
  }
}

void initGestionMode() {
  pinMode(BTN_VERT, INPUT_PULLUP);
  pinMode(BTN_ROUGE, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BTN_VERT), isrVert, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BTN_ROUGE), isrRouge, CHANGE);
  modes[0]=MODE_STANDARD;
  modes[1]=MODE_STANDARD;
  couleurLed(MODE_STANDARD);
}

void gestionModes() {
  // Gestion appui long VERT
  if(appuiVertEnCours && !changementFaitVert && (millis() - tpsAppuiVert > 5000)) {
    if(modes[0] == MODE_STANDARD){
      Serial.println(F("Mode Economique"));
      modes[1] = modes[0];
      modes[0] = MODE_ECONOMIQUE;
      couleurLed(MODE_ECONOMIQUE);
    } else if (modes[0] == MODE_ECONOMIQUE){
      Serial.println(F("Mode Standard"));
      modes[1] = modes[0];
      modes[0] = MODE_STANDARD;
      couleurLed(MODE_STANDARD);
    }
    changementFaitVert = true; // évite de repasser tant que l'appui continue
  }

  // Gestion appui long ROUGE
  if(appuiRougeEnCours && !changementFaitRouge && (millis() - tpsAppuiRouge > 5000)) {
    if (modes[0] != MODE_MAINTENANCE){
      Serial.println(F("Mode Maintenance"));
      modes[1] = modes[0];
      modes[0] = MODE_MAINTENANCE;
      couleurLed(MODE_MAINTENANCE);
    } else {
      Serial.println(F("Retour au mode precedent"));
      int tmp = modes[0];
      modes[0] = modes[1];
      modes[1] = tmp;
      if(modes[0]==MODE_STANDARD) 
        couleurLed(MODE_STANDARD);
      if(modes[0]==MODE_ECONOMIQUE)
        couleurLed(MODE_ECONOMIQUE);
    }
    changementFaitRouge = true;
  }
}

void forcerConfig() {
  modes[1] = modes[0];
  modes[0] = MODE_CONFIGURATION;
  couleurLed(MODE_CONFIGURATION);
}
