#include <stdio.h>
#include <stdlib.h>

#include "utilitaires.h"
#include "graphes.h"

int main(int argc, char **argv){

	char* fichier = malloc(sizeof(char) * 21);
	if(fichier == NULL){
		return EXIT_FAILURE;
	}

	int modeUtilisation = gestion_des_arguments(argc, argv, fichier);
	switch(modeUtilisation){
		case 1:
			printf("Mode encodage.\n");
			break;
		case 2:
			printf("Mode décodage.\n");
			break;
		case -1:
			if(fichier != NULL)
				free(fichier);
			return EXIT_FAILURE;
	}

	//Exemple
	GRAPHE g;
	if(fichier != NULL){
		int resultatLecture = lireFichier(fichier, &g);
		if(resultatLecture < 0){
			fprintf(stderr, "** ERREUR.\n");
			if(fichier != NULL)
				free(fichier);
				return EXIT_FAILURE;
		}
		afficherGraphe(&g);
		supprimerGraphe(&g);
	}

	if(fichier != NULL){
		free(fichier);
	}
  return EXIT_SUCCESS;
}
