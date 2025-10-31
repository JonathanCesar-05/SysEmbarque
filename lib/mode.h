#include <Arduino.h>
#include "gestionLed.h"

#define BTN_VERT 2
#define BTN_ROUGE 3

extern volatile int modes[2]; // [courant, precedent]

volatile bool appuiVertEnCours = false;
volatile unsigned long tpsAppuiVert = 0;
volatile bool changementFaitVert = false;

volatile bool appuiRougeEnCours = false;
volatile unsigned long tpsAppuiRouge = 0;
volatile bool changementFaitRouge = false;