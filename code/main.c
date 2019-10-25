#include <stdio.h>
#include <stdlib.h>

#include "utilitaires.h"
#include "tableau.h"
#include "prufer.h"
#include "graphes.h"

int main(int argc, char **argv){

	char fichier[31];

	ModeUtilisation mode = gestion_des_arguments(argc, argv, fichier);
	switch(mode){
		case encodage:{
			printf("Mode encodage.\n");

			GRAPHE g;
			int resultatLecture = lireFichier(fichier, &g);
			if(resultatLecture < 0){
				return EXIT_FAILURE;
			}
			afficherGraphe(&g);

			sauvegarder_graphe(&g);

			supprimerGraphe(&g);

			return EXIT_SUCCESS;
			break;
		}
		case decodage:{
			printf("Mode décodage.\n");
			int resultatTaille = lire_taille_codage(fichier);
			if(resultatTaille < 0){
				fprintf(stderr, "** ERREUR : Erreur à la lecture de la taille du codage.\n");
				return EXIT_FAILURE;
			}
			CodagePrufer *nvCodage = creer_codage_prufer((unsigned int)resultatTaille);
			if(nvCodage == NULL){
				fprintf(stderr, "** ERREUR : Erreur à la création du codage.\n");
				return EXIT_FAILURE;
			}

			int resultatLecture = lire_codage_prufer(nvCodage, fichier);
			if(resultatLecture < 0){
				fprintf(stderr, "** ERREUR : Erreur à la lecture du codage.\n");
				return EXIT_FAILURE;
			}

			afficher_codage_prufer(nvCodage);

			detruire_codage_prufer(nvCodage);
			return EXIT_SUCCESS;
		}
		case erreur:
			return EXIT_FAILURE;
	}//Fin switch()

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

	/*
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
	*/

  return EXIT_SUCCESS;
}
