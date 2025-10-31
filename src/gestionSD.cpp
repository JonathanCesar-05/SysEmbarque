#include "../lib/gestionSD.h"
#include <SD.h>
#include <time.h>


static char nomFichier[20] = "";
static int revisionCourante = 0;

bool initialiserCarteSD(int brocheCS) {
    if (!SD.begin(brocheCS)) {
        Serial.println("Erreur lors de l'initialisation de la carte SD");
        return false;
    }
    Serial.println("Carte SD initialisée.");
    return true;
}

void obtenirDateActuelle(DateJour *date) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    date->annee = tm.tm_year + 1900;
    date->mois = tm.tm_mon + 1;
    date->jour = tm.tm_mday;
    
    Serial.print("Date du jour : ");
    Serial.print(date->jour);
    Serial.print("/");
    Serial.print(date->mois);
    Serial.print("/");
    Serial.println(date->annee);
}


bool fichierExiste(const char* nom) {
    return SD.exists(nom);
}


bool creerNouveauFichier() {
    DateJour today;
    obtenirDateActuelle(&today);
    
    // Formate directement dans le buffer statique
    snprintf(nomFichier, sizeof(nomFichier), "%02d%02d%02d%d.LOG", 
             today.annee % 100, 
             today.mois, 
             today.jour, 
             revisionCourante);
    
    if (fichierExiste(nomFichier)) {
        Serial.print("Le fichier ");
        Serial.print(nomFichier);
        Serial.println(" existe déjà.");
        return true;
    } else {
        Serial.print("Création du fichier ");
        Serial.println(nomFichier);
        
        File nouveauFichier = SD.open(nomFichier, FILE_WRITE);
        if (nouveauFichier) {
            Serial.println("Fichier correctement créé.");
            nouveauFichier.close();
            return true;
        } else {
            Serial.println("Erreur lors de la création du fichier.");
            return false;
        }
    }
}


// Retourne un pointeur vers le buffer statique
const char* obtenirNomFichierCourant() {
    if (nomFichier[0] == '\0') {  // Si le buffer est vide
        creerNouveauFichier();
    }
    return nomFichier;
}


bool ecrireLigneDonnees(const char* ligneDonnees) {
    if (nomFichier[0] == '\0') {  // Si pas de fichier
        if (!creerNouveauFichier()) {
            return false;
        }
    }
    
    File fichier = SD.open(nomFichier, FILE_WRITE);
    
    if (!fichier) {
        Serial.println("Erreur lors de l'ouverture du fichier.");
        return false;
    }
    
    fichier.println(ligneDonnees);
    fichier.close();
    
    Serial.println("Données écrites avec succès.");
    return true;
}