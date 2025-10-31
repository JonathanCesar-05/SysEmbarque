#ifndef GESTION_SD_H
#define GESTION_SD_H

#include <Arduino.h>

struct DateJour {
    int annee;
    int mois;
    int jour;
};

bool initialiserCarteSD(int brocheCS);
void obtenirDateActuelle(DateJour *date);
bool creerNouveauFichier();
bool ecrireLigneDonnees(const char* ligneDonnees);  
const char* obtenirNomFichierCourant(); 
bool fichierExiste(const char* nomFichier);

#endif
