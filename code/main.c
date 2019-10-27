#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
	Tableau* monTableau = creer_tableau();
	if(monTableau != NULL){
		ajouter_element_tab(monTableau, 1);
		ajouter_element_tab(monTableau, 2);
		ajouter_element_tab(monTableau, 3);
		ajouter_element_tab(monTableau, 2);
		afficher_tableau(monTableau);
		supprimer_element_tab(monTableau, 2);
		afficher_tableau(monTableau);
	}
	if(monTableau != NULL)
		detruire_tableau(monTableau);
	*/

  return EXIT_SUCCESS;
}
