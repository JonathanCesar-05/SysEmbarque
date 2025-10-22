#include "../lib/gestionLed.h"

#define NUM_LEDS  1

ChainableLED led(7, 8, NUM_LEDS);

void initialisation_led() {
    led.init();  // Initialisation de la LED
}

void allumerCouleur(uint8_t rouge, uint8_t vert, uint8_t bleu) {
    led.setColorRGB(0, rouge, vert, bleu);  // Définir les couleurs LED
}

void couleurLed(uint8_t modeActuel) {
    switch (modeActuel) {
        case MODE_STANDARD:         // mode standard
            allumerCouleur(0, 100, 0);  // vert
            break;

        case MODE_CONFIGURATION:     // mode configuration
            allumerCouleur(100, 100, 0);  // jaune
            break;

        case MODE_ECONOMIQUE:        // mode économie
            allumerCouleur(0, 0, 100);  // bleu
            break;

        case MODE_MAINTENANCE:       // mode maintenance
            allumerCouleur(100, 0, 0);  // rouge
            break;

        default:
            break;
    }
}


void blinkLedWithCoef(uint8_t ledIndex, uint8_t r, uint8_t g, uint8_t b, int delayTime, uint8_t coef) {
    led.setColorRGB(ledIndex, r, g, b);  // Allumer la LED avec la couleur spécifiée
    delay(delayTime * coef);             // Garder la LED allumée selon le coefficient
    led.setColorRGB(ledIndex, 0, 0, 0);  // Éteindre la LED
}

void erreurLed(uint8_t nErreur) {
    int delayTime = 200;  // Durée de base du clignotement en millisecondes

    switch (nErreur)
    {
    case ERREUR_RTC:                   // Erreur d'accès à l'horloge RTC
        // intermittente rouge et bleue
        while (true) {
            blinkLedWithCoef(0, 100, 0, 0, delayTime, 1);  // Rouge normal
            blinkLedWithCoef(0, 0, 0, 100, delayTime, 1);  // Bleu normal
        }
        break;

    case ERREUR_GPS:                   // Erreur d’accès aux données du GPS
        // intermittente rouge et jaune
        while (true) {
            blinkLedWithCoef(0, 100, 0, 0, delayTime, 1);  // Rouge normal
            blinkLedWithCoef(0, 100, 100, 0, delayTime, 1);  // Jaune normal
        }
        break;

    case ERREUR_DONNEES_CAPTEUR:         // Erreur accès aux données d’un capteur
        // intermittente rouge et verte
        while (true) {
            blinkLedWithCoef(0, 100, 0, 0, delayTime, 1);  // Rouge normal
            blinkLedWithCoef(0, 0, 100, 0, delayTime, 1);  // Vert normal
        }
        break;

    case ERREUR_DONNEES_INCOHERENTE:       // Données incohérentes - vert 2x plus long
        while (true) {
            blinkLedWithCoef(0, 100, 0, 0, delayTime, 1);  // Rouge normal
            blinkLedWithCoef(0, 0, 100, 0, delayTime, 2);  // Vert avec coef 2
        }
        break;

    case ERREUR_SD_PLEINE:               // Carte SD pleine
        // intermittente rouge et blanche
        while (true) {
            blinkLedWithCoef(0, 100, 0, 0, delayTime, 1);  // Rouge normal
            blinkLedWithCoef(0, 100, 100, 100, delayTime, 1);  // Blanc normal
        }
        break;

    case ERREUR_ECRITURE_SD:             // Erreur d'écriture sur la carte SD - blanc 2x plus long
        while (true) {
            blinkLedWithCoef(0, 100, 0, 0, delayTime, 1);  // Rouge normal
            blinkLedWithCoef(0, 100, 100, 100, delayTime, 2);  // Blanc avec coef 2
        }
        break;

    default:
        break;
    }
}
