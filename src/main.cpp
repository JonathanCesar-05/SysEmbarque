#include "../lib/config.h"
#include "../lib/acquisition.h"
#include "../lib/gestionLed.h"
#include "../lib/mode.h"
#include "../lib/gestionSD.h"
#include "../lib/clock.h"
#include "../lib/gestionErreur.h"

CapteurData mesure;
unsigned long lastAcq = 0;
unsigned long interval = 0;

void setup() {
  Serial.begin(9600);

  initialisation_led();
  couleurLed(MODE_STANDARD);

  initGestionMode();
  init_clock();

  // Initial SD, affiche erreur si KO
  if (!initialiserCarteSD(4)) {
    definirErreur(ERREUR_ECRITURE_SD);
  }

  reset_parameters(cfg);
  interval = cfg.LOG_INTERVAL;
}

void loop() {
  gestionModes();

  // Gestion des erreurs système (LED clignotante dédiée)
  if (erreurActive()) {
    gererClignotementErreur();
    delay(100);
    return;
  }

  // Gestion du mode courant
  switch (modes[0]) {
    case MODE_STANDARD:
      interval = cfg.LOG_INTERVAL;
      if (millis() - lastAcq >= interval) {
        acquisition(&mesure);
        enregistrerMesureSD(&mesure); // fonction à relier (gestionSD)
        lastAcq = millis();
      }
      break;

    case MODE_ECONOMIQUE: {
      static bool gpsFlag = false;
      interval = 2 * cfg.LOG_INTERVAL; // Mode éco : intervalle doublé
      if (millis() - lastAcq >= interval) {
        // Acquisition une fois sur deux sans GPS
        if (gpsFlag) {
          acquisition(&mesure); // Acquisition complète avec GPS
        } else {
          // Version sans GPS
          acquisitionSansGPS(&mesure); // À créer: même fonction, juste sans lecture GPS
        }
        enregistrerMesureSD(&mesure);
        gpsFlag = !gpsFlag;
        lastAcq = millis();
      }
      break;
    }

    case MODE_MAINTENANCE:
      // Affichage capteurs sur Serial uniquement, SD safe à retirer
      acquisition(&mesure);
      afficherDonneesSerial(&mesure); // Créé une fonction qui affiche proprement via Serial
      delay(cfg.LOG_INTERVAL); // Pour éviter un spam sur le port COMM
      break;

    case MODE_CONFIGURATION:
      config(); // Entrée dans menu config Série UART
      // Le retour mode Standard est géré par timeout dans config()
      break;
  }
}
