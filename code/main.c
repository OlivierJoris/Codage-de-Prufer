#include <stdio.h>
#include <stdlib.h>

#include "utilitaires.h"
#include "tableau.h"
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

	/*
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
	*/

	//Test type opaque tableau.
	Tableau* monTableau = creer_tableau(5);
	if(monTableau != NULL){
		modifier_valeur_tableau(monTableau, 4, 3);
		incrementer_valeur_tableau(monTableau, 0);
		afficher_tableau(monTableau);
		modifier_valeur_tableau(monTableau, 3, 5);
		decrementer_valeur_tableau(monTableau, 3);
		printf("Valeur en position 3 : %x\n", recuperer_valeur_tableau(monTableau, 3));
		afficher_tableau(monTableau);
		modifier_taille_tableau(monTableau, 4); //ERREUR
		modifier_valeur_tableau(monTableau, 10, 1); //ERREUR
		incrementer_valeur_tableau(monTableau, 9); //ERREUR
		decrementer_valeur_tableau(monTableau, 8); //ERREUR
		//recuperer_valeur_tableau(monTableau, 7); //ERREUR
		modifier_taille_tableau(monTableau, 5); //ERREUR
		supprimerTableau(monTableau);
	}

	if(fichier != NULL){
		free(fichier);
	}
  return EXIT_SUCCESS;
}
