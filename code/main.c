/* ------------------------------------------------------------------------- *
 * Programme
 * ------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "utilitaires.h"
#include "tableau.h"
#include "prufer.h"
#include "graphes.h"

int main(int argc, char **argv){

	if(argc != 5){
		fprintf(stderr, "** ERREUR : Argument manquant - option inconnue.\n");
		fprintf(stderr, "Format attendu pour les arguments.\n");
		fprintf(stderr, "-m suivi de \"encodage\" ou \"decodage\" en fonction du mode souhaité.\n");
		fprintf(stderr, "-f suivi du chemin vers le fichier ou lire le graphe/codage de Prufer.\n");
		return EXIT_FAILURE;
	}

	char fichier[31];

	ModeUtilisation mode = gestion_des_arguments(argc, argv, fichier);
	switch(mode){
		case encodage:{

			srand(time(NULL)); //Nécessaire pour test_connexite()

			printf("Mode encodage.\n");

			GRAPHE g;
			int resultatLecture = lireFichier(fichier, &g);
			if(resultatLecture < 0){
				fprintf(stderr, "** ERREUR lors de la lecture du graphe.\n");
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

			// La fonction "est_non_oriente" modifiant le graphe de départ, il faut recharger celui-ci.
			resultatLecture = lireFichier(fichier, &g);
			if(resultatLecture < 0){
				fprintf(stderr, "** ERREUR lors de la lecture du graphe.\n");
				return EXIT_FAILURE;
			}

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

			// La fonction "contient_cycle" modifiant le graphe de départ, il faut recharger celui-ci.
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
				//Il faut recharger le graphe car la fonction generer_codage_prufer modifie le graphe de départ.
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

  	return EXIT_SUCCESS;
}
