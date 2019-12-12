/* ------------------------------------------------------------------------- *
 * Analyse des performances
 * ------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "utilitaires.h"
#include "tableau.h"
#include "prufer.h"
#include "graphes.h"

static void generer_codage(unsigned int nbSommets){

    FILE* fichierCodage = fopen("codage_test.txt", "w");
	if(fichierCodage == NULL){
        fprintf(stderr, "** ERREUR à la création du fichier codage_test.txt.\n");
        return;
    }

    fprintf(fichierCodage, "%u\n", nbSommets - 2);

    srand(time(NULL));

    for(size_t i = 0; i < nbSommets - 2; ++i){
        fprintf(fichierCodage, "%u ", (rand() % (nbSommets - 2)) + 1);
    }

    fprintf(fichierCodage, "\n");

    fclose(fichierCodage);
}

static void calculer_temps_decodage(unsigned int nbSommets){

    clock_t debut = clock();

    int resultatTaille = lire_taille_codage("codage_test.txt");

    if(resultatTaille < 0){
        fprintf(stderr, "** ERREUR : Erreur à la lecture de la taille du codage.\n");
        return;
    }

    CodagePrufer *nvCodage = creer_codage_prufer((unsigned int) resultatTaille);
    if(nvCodage == NULL){
        fprintf(stderr, "** ERREUR : Erreur à la création du codage.\n");
        return;
    }

    int resultatLecture = lire_codage_prufer(nvCodage, "codage_test.txt");
    if(resultatLecture < 0){
        fprintf(stderr, "** ERREUR : Erreur à la lecture du codage.\n");
        return;
    }

    GRAPHE g;

    initialiserGraphe(&g);

    resultatLecture = decoder_codage_prufer(&g, nvCodage);

    if(resultatLecture < 0){
        fprintf(stderr, "** ERREUR : Erreur lors du décodage.\n");
        supprimerGraphe(&g);
        return;
    }

    int resultatSauvegarde = sauvegarder_graphe(&g);
    if(resultatSauvegarde < 0){
        fprintf(stderr, "** ERREUR lors de la sauvegarde du graphe.\n");
        supprimerGraphe(&g);
        return;
    }

    clock_t fin = clock();

    FILE* fichierResultatsDecodage = fopen("resultats_decodage.txt", "a");
	if(fichierResultatsDecodage == NULL){
        fprintf(stderr, "** ERREUR à la création du fichier codage_test.txt.\n");
        return;
    }

    fprintf(fichierResultatsDecodage, "Nombre de sommets : %u | Temps : %lf secondes\n", nbSommets, ((double) (fin - debut)) / CLOCKS_PER_SEC);

    fclose(fichierResultatsDecodage);

    detruire_codage_prufer(nvCodage);

    supprimerGraphe(&g);

    return;
}

static void calculer_temps_encodage(unsigned int nbSommets){

    GRAPHE g;
    int resultatLecture = lireFichier("output_graph.txt", &g);
    if(resultatLecture < 0){
        return;
    }

    clock_t debut = clock();

    CodagePrufer* codage = generer_codage_prufer(&g);
    if(codage == NULL){
        fprintf(stderr, "** ERREUR à la génération du codage de Prüfer.\n");
        supprimerGraphe(&g);
        return;
    }else{
        supprimerGraphe(&g);
        resultatLecture = lireFichier("output_graph.txt", &g);
        if(resultatLecture < 0){
            fprintf(stderr, "** ERREUR lors de la lecture du graphe.\n");
            return;
        }
    }

    clock_t fin = clock();

    FILE* fichierResultatsEncodage = fopen("resultats_encodage.txt", "a");
	if(fichierResultatsEncodage == NULL){
        fprintf(stderr, "** ERREUR à la création du fichier codage_test.txt.\n");
        return;
    }

    fprintf(fichierResultatsEncodage, "Nombre de sommets : %u | Temps : %lf secondes\n", nbSommets, ((double) (fin - debut)) / CLOCKS_PER_SEC);

    fclose(fichierResultatsEncodage);

    detruire_codage_prufer(codage);

    supprimerGraphe(&g);

    return;
}

int main(int argc, char **argv){

    if(argc != 2){
        fprintf(stderr, "Veuillez indiquer le nombre de sommets maximum en arguments du programme.\n");
		return EXIT_FAILURE;
	}

    generer_codage(atoi(argv[1]));

    calculer_temps_decodage(atoi(argv[1]));
    calculer_temps_encodage(atoi(argv[1]));

    return 0;
}
