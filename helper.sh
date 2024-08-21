#!/bin/bash

# Vérifier que le nombre d'arguments est suffisant
if [ "$#" -lt 1 ]; then
  echo "Usage: $0 <option> [fichier_test]"
  echo "Options:"
  echo "  -c   Compiler et exécuter un programme C"
  echo "  -b   Vérifier tous les fichiers C avec Betty"
  echo "  -t  Compiler tous les fichiers C avec un fichier test spécifique"
  exit 1
fi

OPTION=$1
TEST_FILE=$2

case $OPTION in
  -c)
    # Compiler le programme
    gcc -Wall -Wextra -pedantic -std=gnu99 -g -DDEBUG *.c -o hsh
    if [ $? -eq 0 ]; then
      echo "Compilation réussie."
      # Exécuter le programme
      ./hsh
    else
      echo "Erreur de compilation."
      exit 1
    fi
    ;;
  -b)
    # Vérifier tous les fichiers C avec Betty
    for file in *.c; do
      betty "$file"
      if [ $? -ne 0 ]; then
        echo "Erreur dans le fichier $file."
        exit 1
      fi
    done
    echo "Tous les fichiers C sont conformes."
    ;;
  -t)
    # Vérifier que le fichier test existe
    if [ ! -f "./tests/$TEST_FILE" ]; then
      echo "Erreur: le fichier test '$TEST_FILE' n'existe pas dans le dossier tests."
      exit 1
    fi

    # Compiler tous les fichiers C avec le fichier test spécifique
    gcc -Wall -Wextra -std=gnu99 $(ls *.c | grep -v '^main\.c$') ./tests/tests.c ./tests/"$TEST_FILE" -lcapstone -g -o test
    if [ $? -eq 0 ]; then
      echo "Compilation réussie."
      # Exécuter le programme
      ./test
    else
      echo "Erreur de compilation."
      exit 1
    fi
    ;;
  *)
    echo "Option invalide: $OPTION"
    echo "Usage: $0 <option> [fichier_test]"
    echo "Options:"
    echo "  -c   Compiler et exécuter un programme C"
    echo "  -t   Compiler et exécuter un programme C avec un fichier test"
    echo "  -b   Vérifier tous les fichiers C avec Betty"
    echo "  -ct  Compiler tous les fichiers C avec un fichier test spécifique"
    exit 1
    ;;
esac
