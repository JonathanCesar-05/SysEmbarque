#ifndef GESTION_ERREUR_H
#define GESTION_ERREUR_H

#include <Arduino.h>
#include "gestionLed.h"


enum erreur {
    ERREUR_RTC,                    // Erreur RTC - Rouge/Bleu
    ERREUR_GPS,                    // Erreur GPS - Rouge/Jaune
    ERREUR_DONNEES_CAPTEUR,        // Erreur accès capteur - Rouge/Vert
    ERREUR_DONNEES_INCOHERENTE,    // Données incohérentes - Rouge/Vert (vert x2)
    ERREUR_SD_PLEINE,              // SD pleine - Rouge/Blanc
    ERREUR_ECRITURE_SD,            // Erreur écriture SD - Rouge/Blanc (blanc x2)
    AUCUNE_ERREUR
};


// Signale une erreur via LED (à appeler dans loop())
void signalerErreur(erreur typeErreur);

// Met à jour le clignotement d'erreur (à appeler dans loop())
void gererClignotementErreur();

// Définit l'erreur active
void definirErreur(erreur typeErreur);

// Obtient le nom de l'erreur en texte
const char* obtenirNomErreur(erreur typeErreur);

// Efface l'erreur active
void effacerErreur();

// Retourne vrai si une erreur est active
bool erreurActive();

#endif
