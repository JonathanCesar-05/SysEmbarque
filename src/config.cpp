#include <EEPROM.h>
#include <Arduino.h>
#include <time.h>
#include "config.h"

// Recharge les paramètres enregistrés ou démarre avec des valeurs par défaut
void loadConfig() {
  EEPROM.get(0, cfg);
  if (cfg.version == 0xFFFF || cfg.version == 0) { // si EEPROM vide ou non initialisée
    cfg.logInterval = 10;
    cfg.timeout = 5;
    cfg.fileMaxSize = 100;
    cfg.version = 1;
    EEPROM.put(0, cfg);
  }
}

// Sauvegarde des modifications dans l’EEPROM
void saveConfig() {
  cfg.version++;
  EEPROM.put(0, cfg);
  Serial.println(F("Paramètres sauvegardés !"));
}

// Affiche le menu texte
void printMenu() {
  Serial.println();
  Serial.println(F("=== MODE CONFIGURATION ==="));
  Serial.println(F("1. Changer LOG_INTERVAL"));
  Serial.println(F("2. Changer TIMEOUT"));
  Serial.println(F("3. Changer FILE_MAX_SIZE"));
  Serial.println(F("4. Afficher les paramètres"));
  Serial.println(F("5. Réinitialiser par défaut"));
  Serial.println(F("6. Quitter configuration"));
  Serial.print(F("> Votre choix : "));
}

// Affiche les valeurs actuelles des paramètres
void showConfig() {
  Serial.println();
  Serial.println(F("--- Paramètres actuels ---"));
  Serial.print(F("LOG_INTERVAL : ")); Serial.println(cfg.logInterval);
  Serial.print(F("TIMEOUT      : ")); Serial.println(cfg.timeout);
  Serial.print(F("FILE_MAX_SIZE: ")); Serial.println(cfg.fileMaxSize);
  Serial.print(F("VERSION      : ")); Serial.println(cfg.version);
}

// Fonction principale du mode configuration
void modeConfiguration() {
  Serial.println(F("Entrée dans le mode CONFIGURATION"));
  loadConfig();
  printMenu();
  lastActivity = millis();

  while (true) {
    // Sortie automatique après 30 minutes d’inactivité
    if (millis() - lastActivity >= CONFIG_TIMEOUT_MS) {
      Serial.println(F("\nInactivité détectée → retour au mode STANDARD"));
      break;
    }

    // Lecture du choix dans le menu
    if (Serial.available()) {
      int choix = Serial.parseInt();
      lastActivity = millis(); // activité détectée => reset du timer

      switch (choix) {
        case 1:
          Serial.print(F("Nouvelle valeur LOG_INTERVAL (secondes) : "));
          while (!Serial.available());
          cfg.logInterval = Serial.parseInt();
          saveConfig();
          break;

        case 2:
          Serial.print(F("Nouvelle valeur TIMEOUT (secondes) : "));
          while (!Serial.available());
          cfg.timeout = Serial.parseInt();
          saveConfig();
          break;

        case 3:
          Serial.print(F("Nouvelle valeur FILE_MAX_SIZE (Ko) : "));
          while (!Serial.available());
          cfg.fileMaxSize = Serial.parseInt();
          saveConfig();
          break;

        case 4:
          showConfig();
          break;

        case 5:
          Serial.println(F("Réinitialisation des valeurs par défaut..."));
          cfg.logInterval = 10;
          cfg.timeout = 5;
          cfg.fileMaxSize = 100;
          cfg.version = 1;
          EEPROM.put(0, cfg);
          Serial.println(F("Valeurs par défaut remises !"));
          break;

        case 6:
          Serial.println(F("Sortie du mode configuration..."));
          return; // quitte la fonction

        default:
          Serial.println(F("Choix invalide."));
          break;
      }

      printMenu();
    }
  }
}
