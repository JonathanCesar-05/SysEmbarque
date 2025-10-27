# --- Script de Compilation ---
# Ce script va transformer notre code source en langage machine.
# Le script de téléversement permettra de transferer notre code source à l'arduino
# Installer avr-libc // avr-gcc

#!/bin/bash
MCU=atmega328p          # Type de carte, par exemple Arduino Uno
F_CPU=16000000UL        # Fréquence, ici 16 MHz
TARGET=main             # Nom du binaire de sortie
SRC=main.cpp            # Nom du fichier source


echo "Compilation du code..."
avr-gcc -std=c++11 -Wall -g -Os -mmcu=$MCU -DF_CPU=$F_CPU -o $TARGET.bin $SRC


# $? contient le code retour de la dernière commande (avr-gcc ...).
# Si la valeur est 0, cela signifie que la compilation s’est terminée sans erreur.
#  Utilise l’outil avr-objcopy pour extraire les sections .text (code), .data (données) du binaire, 
# et les convertir en fichier Intel HEX (.hex)


if [ $? -eq 0 ]; then
  echo "Conversion en .hex"
  avr-objcopy -j .text -j .data -O ihex $TARGET.bin $TARGET.hex
  echo "Succès : $TARGET.hex est prêt."
else
  echo "Erreur : compilation échouée."
fi


# "avr-gcc" --> Lance le compilateur C/C++ adapté aux microcontrôleurs AVR (famille Arduino Uno, Mega, Nano…).
# "-std=c++11" --> Indique au compilateur d’utiliser la norme C++11 (version moderne du langage C++)
# "-Wall" --> Active l’affichage de presque tous les avertissements lors de la compilation
# "-g" --> Génère des informations de débogage dans le binaire
# "-Os" --> Optimise le code compilé pour minimiser la taille du binaire
# "-mmcu=$MCU" --> Spécifie la cible matériel (le microcontrôleur, ex : atmega328p pour Arduino Uno) afin de générer un code machine compatible.
# "-DF_CPU=$F_CPU" --> Définit une macro F_CPU (par exemple 16 000 000 pour 16 MHz) qui sera utilisée dans le code pour indiquer la fréquence d’horloge du microcontrôleur.
# "-o $TARGET.bin" --> Spécifie le nom du fichier binaire de sortie. Ici, la variable $TARGET devient le nom du binaire généré, suivi de .bin.
# "$SRC" --> Liste un ou plusieurs fichiers source à compiler (par exemple, main.cpp).