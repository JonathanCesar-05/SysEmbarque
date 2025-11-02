#include <Arduino.h>
#include "gestionLed.h"

#define BTN_VERT 2
#define BTN_ROUGE 3

extern volatile int modes[2]; // [courant, precedent]
extern volatile bool appuiVertEnCours;
extern volatile unsigned long tpsAppuiVert;
extern volatile bool changementFaitVert;
extern volatile bool appuiRougeEnCours;
extern volatile unsigned long tpsAppuiRouge;
extern volatile bool changementFaitRouge;

void isrVert();
void isrRouge();
void initGestionMode();
void gestionModes();
void forcerConfig();