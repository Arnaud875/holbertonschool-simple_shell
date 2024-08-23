#!/bin/bash

# Vérifier que le nombre d'arguments est suffisant
if [ "$#" -lt 1 ]; then
	echo "Usage: $0 <option> [fichier_test]"
	echo "Options:"
	echo "  -c  Compiler et exécuter un programme C"
	echo "  -t  Compiler et exécuter un programme C avec un fichier test"
	exit 1
fi

OPTION=$1
TEST_FILE=$2

case $OPTION in
	-c)
		# Compiler le programme
		gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
		if [ $? -eq 0 ]; then
			echo "Compilation réussie."
			# Exécuter le programme
			./hsh
		else
			echo "Erreur de compilation."
			exit 1
		fi
		;;
	-t)
		# Vérifier que le fichier test existe
		if [ ! -f "$TEST_FILE" ]; then
			echo "Erreur: le fichier test '$TEST_FILE' n'existe pas."
			exit 1
		fi

		# Compiler le programme
		gcc -Wall -Werror -Wextra -pedantic -std=gnu99 ./tests/"$TEST_FILE" -o test
		if [ $? -eq 0 ]; then
			echo "Compilation réussie."
			# Exécuter le programme avec le fichier test
			./test
		else
			echo "Erreur de compilation."
			exit 1
		fi
		;;
	*)
		echo "Option invalide: $OPTION"
		echo "Usage: $0 <option> <fichier_source> [fichier_test]"
		echo "Options:"
		echo "  -c  Compiler et exécuter un programme C"
		echo "  -t  Compiler et exécuter un programme C avec un fichier test"
		exit 1
		;;
esac
