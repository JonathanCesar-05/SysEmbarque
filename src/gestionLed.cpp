#include "../lib/gestionLed.h"

#define NUM_LEDS 1

// ============================================================================
// Instance globale de la LED chainable (pins 7 et 8)
// IMPORTANT : Doit être globale pour être accessible dans toutes les fonctions
// ============================================================================
ChainableLED led(7, 8, NUM_LEDS);

// ============================================================================
// Fonction: initialisation_led
// Description: Initialise la LED chainable et l'éteint au démarrage
// ============================================================================
void initialisation_led() {
    // L'objet led est déjà initialisé par son constructeur
    // On éteint juste la LED au démarrage
    led.setColorRGB(0, 0, 0, 0);
    Serial.println(F("LED initialisee et eteinte."));
}

// ============================================================================
// Fonction: allumerCouleur
// Description: Allume la LED avec une couleur RGB spécifique
// Paramètres:
//   - rouge, vert, bleu: Intensité de chaque couleur (0-255)
// ============================================================================
void allumerCouleur(uint8_t rouge, uint8_t vert, uint8_t bleu) {
    led.setColorRGB(0, rouge, vert, bleu);
}

// ============================================================================
// Fonction: eteindreLed
// Description: Éteint complètement la LED
// ============================================================================
void eteindreLed() {
    led.setColorRGB(0, 0, 0, 0);
}

// ============================================================================
// Fonction: couleurLed
// Description: Change la couleur de la LED selon le mode actuel
// Paramètres:
//   - modeActuel: Mode du système (enum mode)
// ============================================================================
void couleurLed(uint8_t modeActuel) {
    switch (modeActuel) {
        case MODE_STANDARD:
            allumerCouleur(0, 255, 0);  // Vert
            break;

        case MODE_CONFIGURATION:
            allumerCouleur(255, 255, 0);  // Jaune
            break;

        case MODE_ECONOMIQUE:
            allumerCouleur(0, 0, 255);  // Bleu
            break;

        case MODE_MAINTENANCE:
            allumerCouleur(255, 0, 0);  // Rouge
            break;

        default:
            eteindreLed();
            break;
    }
}
