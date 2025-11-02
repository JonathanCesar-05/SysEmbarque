#ifndef GESTION_SD_H
#define GESTION_SD_H

#include <Arduino.h>
// Ajoute l'inclusion SdFat
#include <SdFat.h>

struct DateJour {
    int annee;
    int mois;
    int jour;
};

// Fonctions disponibles
bool initialiserCarteSD(int brocheCS);
void obtenirDateActuelleRTC(DateJour *date); // Corrigé pour correspondre au corps du .cpp donné précédemment
bool creerNouveauFichier();
bool ecrireLigneDonnees(const char* ligneDonnees);
const char* obtenirNomFichierCourant();
bool fichierExiste(const char* nomFichier);
void definirTailleMaxFichier(uint32_t taille);
uint32_t obtenirTailleFichierCourant();
void incrementerRevision();
bool verifierEspaceSD();

#endif
