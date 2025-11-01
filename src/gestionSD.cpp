#include "../lib/gestionSD.h"
#include "../lib/clock.h" // Pour utiliser le RTC DS1307
#include "../lib/gestionErreur.h"
#include <SD.h>

static char nomFichier[20] = "";
static int revisionCourante = 0;
static uint32_t tailleMaxFichier = 4096;  // 4 Ko par défaut (configurable)

// ============================================================================
// Fonction: initialiserCarteSD
// Description: Initialise la carte SD
// ============================================================================
bool initialiserCarteSD(int brocheCS) {
    if (!SD.begin(brocheCS)) {
        Serial.println(F("Erreur lors de l'initialisation de la carte SD"));
        definirErreur(ERREUR_ECRITURE_SD);
        return false;
    }
    Serial.println(F("Carte SD initialisee."));
    return true;
}

// ============================================================================
// Fonction: obtenirDateActuelleRTC
// Description: Obtient la date depuis le RTC DS1307
// ============================================================================
void obtenirDateActuelleRTC(DateJour *date) {
    byte second, minute, hour, day, month, year;
    getDS1307Time(&second, &minute, &hour, &day, &month, &year);
    
    date->annee = year;    // Déjà en format 20XX depuis getDS1307Time
    date->mois = month;
    date->jour = day;
    
    Serial.print(F("Date du jour : "));
    Serial.print(date->jour);
    Serial.print(F("/"));
    Serial.print(date->mois);
    Serial.print(F("/"));
    Serial.println(date->annee);
}

// ============================================================================
// Fonction: fichierExiste
// Description: Vérifie si un fichier existe sur la carte SD
// ============================================================================
bool fichierExiste(const char* nom) {
    return SD.exists(nom);
}

// ============================================================================
// Fonction: definirTailleMaxFichier
// Description: Définit la taille maximale d'un fichier (configurable)
// ============================================================================
void definirTailleMaxFichier(uint32_t taille) {
    tailleMaxFichier = taille;
    Serial.print(F("Taille max fichier definie : "));
    Serial.print(tailleMaxFichier);
    Serial.println(F(" octets"));
}

// ============================================================================
// Fonction: obtenirTailleFichierCourant
// Description: Retourne la taille du fichier courant
// ============================================================================
uint32_t obtenirTailleFichierCourant() {
    if (nomFichier[0] == '\0') return 0;
    
    File fichier = SD.open(nomFichier, FILE_READ);
    if (!fichier) return 0;
    
    uint32_t taille = fichier.size();
    fichier.close();
    return taille;
}

// ============================================================================
// Fonction: incrementerRevision
// Description: Incrémente le numéro de révision et crée un nouveau fichier
// ============================================================================
void incrementerRevision() {
    revisionCourante++;
    if (revisionCourante > 9) {
        revisionCourante = 0;  // Retour à 0 après 9
    }
    Serial.print(F("Revision incrementee : "));
    Serial.println(revisionCourante);
}

// ============================================================================
// Fonction: creerNouveauFichier
// Description: Crée un nouveau fichier basé sur la date et la révision
// Format: AAMMJJR.LOG (ex: 25110100.LOG pour 01/11/2025, révision 0)
// ============================================================================
bool creerNouveauFichier() {
    DateJour today;
    obtenirDateActuelleRTC(&today);
    
    // Formate le nom du fichier : AAMMJJR.LOG
    snprintf(nomFichier, sizeof(nomFichier), "%02d%02d%02d%d.LOG", 
             today.annee % 100,  // 2 derniers chiffres de l'année
             today.mois, 
             today.jour, 
             revisionCourante);
    
    if (fichierExiste(nomFichier)) {
        Serial.print(F("Le fichier "));
        Serial.print(nomFichier);
        Serial.println(F(" existe deja."));
        return true;
    } else {
        Serial.print(F("Creation du fichier "));
        Serial.println(nomFichier);
        
        File nouveauFichier = SD.open(nomFichier, FILE_WRITE);
        if (nouveauFichier) {
            // Écriture d'un en-tête (optionnel)
            nouveauFichier.println(F("datetime,temp,pressure,altitude,humidity,light,gps"));
            nouveauFichier.close();
            Serial.println(F("Fichier correctement cree."));
            return true;
        } else {
            Serial.println(F("Erreur lors de la creation du fichier."));
            definirErreur(ERREUR_ECRITURE_SD);
            return false;
        }
    }
}

// ============================================================================
// Fonction: obtenirNomFichierCourant
// Description: Retourne le nom du fichier courant
// ============================================================================
const char* obtenirNomFichierCourant() {
    if (nomFichier[0] == '\0') {
        creerNouveauFichier();
    }
    return nomFichier;
}

// ============================================================================
// Fonction: ecrireLigneDonnees
// Description: Écrit une ligne de données dans le fichier courant
// Gère automatiquement la création de nouveaux fichiers si taille dépassée
// ============================================================================
bool ecrireLigneDonnees(const char* ligneDonnees) {
    // Si pas de fichier, en créer un
    if (nomFichier[0] == '\0') {
        if (!creerNouveauFichier()) {
            return false;
        }
    }
    
    // Vérifier la taille du fichier actuel
    uint32_t tailleActuelle = obtenirTailleFichierCourant();
    uint32_t tailleLigne = strlen(ligneDonnees) + 2;  // +2 pour \r\n
    
    // Si ajout de la ligne dépasse la taille max, créer nouveau fichier
    if (tailleActuelle + tailleLigne >= tailleMaxFichier) {
        Serial.println(F("Taille max atteinte, creation nouveau fichier..."));
        incrementerRevision();
        if (!creerNouveauFichier()) {
            return false;
        }
    }
    
    // Ouverture du fichier pour écriture
    File fichier = SD.open(nomFichier, FILE_WRITE);
    
    if (!fichier) {
        Serial.println(F("Erreur lors de l'ouverture du fichier."));
        definirErreur(ERREUR_ECRITURE_SD);
        return false;
    }
    
    // Écriture de la ligne
    fichier.println(ligneDonnees);
    fichier.close();
    
    Serial.println(F("Donnees ecrites avec succes."));
    return true;
}

// ============================================================================
// Fonction: verifierEspaceSD
// Description: Vérifie si la carte SD a assez d'espace
// Retour: true si OK, false si pleine
// ============================================================================
bool verifierEspaceSD() {
    // Note: SD.h ne fournit pas de méthode native pour vérifier l'espace libre
    // Pour l'instant on vérifie juste si on peut créer un fichier test
    
    File testFile = SD.open("test.tmp", FILE_WRITE);
    if (!testFile) {
        definirErreur(ERREUR_SD_PLEINE);
        return false;
    }
    testFile.close();
    SD.remove("test.tmp");
    return true;
}
