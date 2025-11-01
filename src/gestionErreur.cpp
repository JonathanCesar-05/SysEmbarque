#include "../lib/gestionErreur.h"

// Variables pour la gestion des clignotements
static erreur erreurCourante = AUCUNE_ERREUR;
static unsigned long previousMillis = 0;
static bool couleurPrincipale = true;  // true = rouge, false = couleur secondaire

// ============================================================================
// Fonction: obtenirNomErreur
// Description: Retourne le nom de l'erreur sous forme de texte
// ============================================================================
const char* obtenirNomErreur(erreur typeErreur) {
    switch (typeErreur) {
        case ERREUR_RTC:
            return "Erreur RTC";
        case ERREUR_GPS:
            return "Erreur GPS";
        case ERREUR_DONNEES_CAPTEUR:
            return "Erreur capteur";
        case ERREUR_DONNEES_INCOHERENTE:
            return "Donnees incoherentes";
        case ERREUR_SD_PLEINE:
            return "Carte SD pleine";
        case ERREUR_ECRITURE_SD:
            return "Erreur ecriture SD";
        default:
            return "Aucune erreur";
    }
}

// ============================================================================
// Fonction: definirErreur
// Description: Définit l'erreur active et affiche un message
// ============================================================================
void definirErreur(erreur typeErreur) {
    if (typeErreur != AUCUNE_ERREUR) {
        Serial.print(F("ERREUR DETECTEE: "));
        Serial.println(obtenirNomErreur(typeErreur));
    }
    erreurCourante = typeErreur;
    previousMillis = millis();
    couleurPrincipale = true;
}

// ============================================================================
// Fonction: effacerErreur
// Description: Efface l'erreur active
// ============================================================================
void effacerErreur() {
    erreurCourante = AUCUNE_ERREUR;
    Serial.println(F("Erreur effacee."));
}

// ============================================================================
// Fonction: erreurActive
// Description: Retourne true si une erreur est active
// ============================================================================
bool erreurActive() {
    return erreurCourante != AUCUNE_ERREUR;
}

// ============================================================================
// Fonction: gererClignotementErreur
// Description: Met à jour le clignotement LED selon l'erreur active
// Note: À appeler dans loop()
// ============================================================================
void gererClignotementErreur() {
    if (erreurCourante == AUCUNE_ERREUR) {
        return;  // Pas d'erreur active
    }

    unsigned long currentMillis = millis();
    unsigned long intervalRouge = 1000;          // Intervalle rouge par défaut
    unsigned long intervalSecondaire = 1000;     // Intervalle couleur secondaire par défaut

    // Adapter les intervalles selon le type d'erreur
    switch (erreurCourante) {
        case ERREUR_DONNEES_INCOHERENTE:
            intervalSecondaire = 2000;  // Vert 2x plus long
            break;
            
        case ERREUR_ECRITURE_SD:
            intervalSecondaire = 2000;  // Blanc 2x plus long
            break;
            
        default:
            break;
    }

    // Déterminer l'intervalle actuel
    unsigned long intervalActuel = couleurPrincipale ? intervalRouge : intervalSecondaire;

    // Vérifier si l'intervalle est écoulé
    if (currentMillis - previousMillis >= intervalActuel) {
        previousMillis = currentMillis;

        if (couleurPrincipale) {
            // Afficher rouge pour toutes les erreurs
            allumerCouleur(255, 0, 0);
        } else {
            // Afficher la couleur secondaire selon l'erreur
            switch (erreurCourante) {
                case ERREUR_RTC:
                    allumerCouleur(0, 0, 255);  // Bleu
                    break;
                    
                case ERREUR_GPS:
                    allumerCouleur(255, 255, 0);  // Jaune
                    break;
                    
                case ERREUR_DONNEES_CAPTEUR:
                    allumerCouleur(0, 255, 0);  // Vert
                    break;
                    
                case ERREUR_DONNEES_INCOHERENTE:
                    allumerCouleur(0, 255, 0);  // Vert (2x plus long)
                    break;
                    
                case ERREUR_SD_PLEINE:
                    allumerCouleur(255, 255, 255);  // Blanc
                    break;
                    
                case ERREUR_ECRITURE_SD:
                    allumerCouleur(255, 255, 255);  // Blanc (2x plus long)
                    break;
                    
                default:
                    allumerCouleur(255, 255, 255);  // Blanc par défaut
                    break;
            }
        }

        // Alterner entre rouge et couleur secondaire
        couleurPrincipale = !couleurPrincipale;
    }
}

// ============================================================================
// Fonction: signalerErreur 
// Description: Définit une erreur et affiche un message
// ============================================================================
void signalerErreur(erreur typeErreur) {
    definirErreur(typeErreur);
}
