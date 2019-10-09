#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utilitaires.h"

int gestion_des_arguments(int argc, char **argv, char *source){
	if(argv == NULL || source == NULL){
		fprintf(stderr, "** ERREUR : Gestion des arguments.\n");
		return -1;
	}

	const char *arguments = ":m:f:"; //Format attendu des options.
	int optionCourante, modeUtilisation;

	while((optionCourante = getopt(argc, argv, arguments)) != EOF){
		switch(optionCourante){
			case 'm': //Mode d'utilisation.
				if((!strcmp(optarg, "encodage")) || (!strcmp(optarg, "decodage"))){ //Mode connu.
					printf("Mode d'utilisation : %s\n", optarg);
					if(!strcmp(optarg, "encodage"))
						modeUtilisation = 1;
					else
						modeUtilisation = 2;
					break;
				}else{ //Mode inconnu.
					fprintf(stderr, "** ERREUR : argument -m. Soit \"encodage\" soit \"decodage\".\n");
					return -1;
				}
			case 'f': //Fichier source.
				printf("Fichier source/destination : %s\n", optarg);
				strcpy(source, optarg);
				break;
			case '?': //Option inconnue.
			case ':': //Argument manquant.
				fprintf(stderr, "** ERREUR : Argument manquant - option inconnue.\n");
				fprintf(stderr, "Format attendu pour les arguments.\n");
				fprintf(stderr, "-m suivi de \"encodage\" ou \"decodage\" en fonction du mode souhaité.\n");
				fprintf(stderr, "-f suivi du chemin vers le fichier ou lire le graphe/codage de Prufer.\n");
				return -1;
		}//Fin switch()
	}//Fin while()
	fprintf(stderr, "\n");

	return modeUtilisation;
}//Fin gestion_des_arguments()
