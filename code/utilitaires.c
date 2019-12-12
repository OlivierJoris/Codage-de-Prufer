/* ------------------------------------------------------------------------- *
 * Fichier qui contient la fonction pour gérer les arguments du programme
 * et générer un nombre aléatoire entre 2 bornes.
 * ------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "utilitaires.h"

ModeUtilisation gestion_des_arguments(int argc, char **argv, char *source){
	if(argv == NULL || source == NULL){
		fprintf(stderr, "** ERREUR : Gestion des arguments.\n");
		return erreur;
	}

	const char *arguments = ":m:f:"; //Format attendu des options.
	int optionCourante;
	ModeUtilisation mode = erreur;

	while((optionCourante = getopt(argc, argv, arguments)) != EOF){
		switch(optionCourante){
			case 'm': //Mode d'utilisation.
				if((!strcmp(optarg, "encodage")) || (!strcmp(optarg, "decodage"))){ //Mode connu.
					printf("Mode d'utilisation : %s\n", optarg);
					if(!strcmp(optarg, "encodage"))
						mode = encodage;
					else
						mode = decodage;
				}else{ //Mode inconnu.
					fprintf(stderr, "** ERREUR : argument -m. Soit \"encodage\" soit \"decodage\".\n");
					return erreur;
				}
				break;
			case 'f': //Fichier source.
				printf("Fichier source : %s\n", optarg);
				strcpy(source, optarg);
				break;
			case '?': //Option inconnue.
				fprintf(stderr, "** ERREUR : Argument manquant - option inconnue.\n");
				fprintf(stderr, "Format attendu pour les arguments.\n");
				fprintf(stderr, "-m suivi de \"encodage\" ou \"decodage\" en fonction du mode souhaité.\n");
				fprintf(stderr, "-f suivi du chemin vers le fichier ou lire le graphe/codage de Prufer.\n");
				return erreur;
			case ':': //Argument manquant.
				fprintf(stderr, "** ERREUR : Argument manquant - option inconnue.\n");
				fprintf(stderr, "Format attendu pour les arguments.\n");
				fprintf(stderr, "-m suivi de \"encodage\" ou \"decodage\" en fonction du mode souhaité.\n");
				fprintf(stderr, "-f suivi du chemin vers le fichier ou lire le graphe/codage de Prufer.\n");
				return erreur;
		}//Fin switch()
	}//Fin while()
	printf("\n");

	return mode;
}//Fin gestion_des_arguments()

int generer_nombre_aleatoire(const int borneMin, const int borneMax){
	if(borneMin > borneMax){
		fprintf(stderr, "La borne min est plus grande que la borne max.\n");
		return EXIT_FAILURE;
	}

	int nombreAleatoire = rand() % (borneMax - borneMin + 1) + borneMin;

	return nombreAleatoire;
}//Fin generer_nombre_aleatoire()
