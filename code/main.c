/* ------------------------------------------------------------------------- *
 * Programme
 * ------------------------------------------------------------------------- */

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

			bool testConnexite = test_connexite(&g);
			if(testConnexite){
				printf("Le graphe est connexe.\n");
			}else{
				fprintf(stderr, "Le graphe n'est pas connexe donc le graphe n'est pas un arbre.\n");
				fprintf(stderr, "Le codage de Prüfer s'applique uniquement aux arbres donc on ne peut pas chercher le codage de Prüfer associé au graphe donné.\n");
				supprimerGraphe(&g);
				return EXIT_FAILURE;
			}

			bool estNonOriente = est_non_oriente(&g);
			if(!estNonOriente){
				fprintf(stderr, "Le graphe n'est pas non-orienté donc le graphe n'est pas un arbre.\n");
				fprintf(stderr, "Le codage de Prüfer s'applique uniquement aux arbres donc on ne peut pas chercher le codage de Prüfer associé au graphe donné.\n");
				supprimerGraphe(&g);
				return EXIT_FAILURE;
			}else{
				printf("Le graphe est non-orienté.\n");
				supprimerGraphe(&g);
			}

			//Il faut également vérifier que le graphe ne contient pas de cycle.
			bool contientCycle = contient_cycle(&g);
			if(contientCycle){
				fprintf(stderr, "Le graphe contient au moins un cycle donc le graphe n'est pas un arbre.\n");
				fprintf(stderr, "Le codage de Prüfer s'applique uniquement aux arbres donc on ne peut pas chercher le codage de Prüfer associé au graphe donné.\n");
				supprimerGraphe(&g);
				return EXIT_FAILURE;
			}else{
				printf("Le graphe ne contient pas de cycle.\n");
				supprimerGraphe(&g);
			}

			resultatLecture = lireFichier(fichier, &g);
			if(resultatLecture < 0){
				fprintf(stderr, "** ERREUR lors de la lecture du graphe.\n");
				return EXIT_FAILURE;
			}

			CodagePrufer* codage = generer_codage_prufer(&g);
			if(codage == NULL){
				fprintf(stderr, "** ERREUR à la génération du codage de Prüfer.\n");
				supprimerGraphe(&g);
				return EXIT_FAILURE;
			}else{
				supprimerGraphe(&g);
				resultatLecture = lireFichier(fichier, &g);
				if(resultatLecture < 0){
					fprintf(stderr, "** ERREUR lors de la lecture du graphe.\n");
					return EXIT_FAILURE;
				}
			}

			afficher_codage_prufer(codage);

			detruire_codage_prufer(codage);

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

			GRAPHE g;

			initialiserGraphe(&g);

			resultatLecture = decoder_codage_prufer(&g, nvCodage);

			if(resultatLecture < 0){
				fprintf(stderr, "** ERREUR : Erreur lors du décodage.\n");
				supprimerGraphe(&g);
				return EXIT_FAILURE;
			}

			printf("Le graphe associé au codage de Prüfer: \n");

			afficher_codage_prufer(nvCodage);

			printf("est tel que:\n");

			afficherGraphe(&g);

			int resultatSauvegarde = sauvegarder_graphe(&g);
			if(resultatSauvegarde < 0){
				fprintf(stderr, "** ERREUR lors de la sauvegarde du graphe.\n");
				supprimerGraphe(&g);
				return EXIT_FAILURE;
			}

			detruire_codage_prufer(nvCodage);

			supprimerGraphe(&g);

			return EXIT_SUCCESS;
			break;
		}
		case erreur:
			return EXIT_FAILURE;
	}//Fin switch()

	/*************************************************************************
	*																		 *
	*																		 *
	* Tests des fonctions auxiliaires au programme.							 *
	*																		 *
	*																		 *
	**************************************************************************/

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
		ajouter_element_tab(monTableau, 4);
		ajouter_element_tab(monTableau, 3);
		ajouter_element_tab(monTableau, 2);
		printf("1er tableau : \n");
		afficher_tableau(monTableau);
	}else{
		fprintf(stderr, "** ERREUR à la création de monTableau.\n");
		return EXIT_FAILURE;
	}

	Tableau* mon2Tableau = creer_tableau();
	if(mon2Tableau != NULL){
		ajouter_element_tab(mon2Tableau, 1);
		ajouter_element_tab(mon2Tableau, 6);
		ajouter_element_tab(mon2Tableau, 3);
		ajouter_element_tab(mon2Tableau, 2);
		printf("2ème tableau :\n");
		afficher_tableau(mon2Tableau);
	}else{
		fprintf(stderr, "** ERREUR à la création de mon2Tableau.\n");
		detruire_tableau(monTableau);
		return EXIT_FAILURE;
	}
	*/
	/*
	//Test copie tableau
	printf("\nmon2Tableau avant copie.\n");
	afficher_tableau(mon2Tableau);
	int resultatCopie = copier_tableau(monTableau, mon2Tableau);
	if(resultatCopie < 0){
		fprintf(stderr, "** ERREUR lors de la copie.\n");
		return EXIT_FAILURE;
	}else{
		printf("mon2Tableau après copie.\n");
		afficher_tableau(mon2Tableau);
	}
	*/
	/* Test union tab
	Tableau* tabUnion = union_tab(monTableau, mon2Tableau);
	if(tabUnion != NULL){
		printf("Union des 2 tableaux : \n");
		afficher_tableau(tabUnion);
	}else{
		fprintf(stderr, "** ERREUR lors de l'union des 2 tableaux.\n");
		detruire_tableau(monTableau);
		detruire_tableau(mon2Tableau);
		return EXIT_FAILURE;
	}
	*/

	/* Test égalité tableaux
	bool testEgalite = egalite_tableaux(monTableau, mon2Tableau);
	if(testEgalite)
		printf("Les tableaux monTableau et mon2Tableau sont les mêmes.\n");
	else
		printf("Les tableaux monTableau et mon2Tableau ne sont PAS les mêmes.\n");
	*/

	/*
	//Test difference tableaux.
	int resultatDifference = difference_tableaux(monTableau, mon2Tableau);
	printf("Différence monTableau\\mon2Tableau.\n");
	afficher_tableau(monTableau);
	if(resultatDifference == 0)
		printf("Différence OK.\n");
	else
		printf("Différence ratée.\n");
	*/
	/*
	if(monTableau != NULL)
		detruire_tableau(monTableau);

	if(mon2Tableau != NULL)
		detruire_tableau(mon2Tableau);

	*/
	/*
	if(tabUnion != NULL)
		detruire_tableau(tabUnion);
	*/
  	return EXIT_SUCCESS;
}
