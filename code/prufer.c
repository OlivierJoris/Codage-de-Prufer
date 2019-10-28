#include <stdio.h>
#include <stdlib.h>

#include "prufer.h"

CodagePrufer *creer_codage_prufer(unsigned int taille){

	CodagePrufer *nvCodage = malloc(sizeof(CodagePrufer));
	if(nvCodage == NULL){
		fprintf(stderr, "** ERREUR : Erreur à l'allocation du codage de Prüfer.\n");
		return NULL;
	}

	nvCodage->taille = taille;
	nvCodage->suitePrufer = malloc(sizeof(int) * taille);
	if(nvCodage->suitePrufer == NULL){
		fprintf(stderr, "** ERREUR : Erreur à l'allocation de la suite de Prüfer.\n");
		free(nvCodage);
		return NULL;
	}

	return nvCodage;
}//Fin creer_codage_prufer()

void detruire_codage_prufer(CodagePrufer *codage){
	if(codage == NULL)
		return;

	if(codage->suitePrufer != NULL)
		free(codage->suitePrufer);

	free(codage);
	return;
}//Fin detruire_codage_prufer()

void afficher_codage_prufer(CodagePrufer *codage){
	if(codage == NULL){
		fprintf(stderr, "Pointeur vers codage vaut NULL\n");
		return;
	}
	if(codage->suitePrufer == NULL){
		fprintf(stderr, "Pointeur vers la suite de Prüfer vaut NULL\n");
		return;
	}

	printf("Codage : ");

	for(unsigned int i = 0; i < codage->taille; i++){
		printf("%d ", codage->suitePrufer[i]);
	}
	printf("\n");
}//Fin afficher_codage_prufer()

int lire_taille_codage(char *nomFichier){
	if(nomFichier == NULL){
		fprintf(stderr, "Pointeur vers nomFichier vaut NULL\n");
		return -1;
	}

	FILE* fichierCodage = fopen(nomFichier, "r");
	if(fichierCodage == NULL){
		fprintf(stderr, "Impossible d'ouvrir le fichier.\n");
		return -2;
	}

	unsigned int taille;

	fscanf(fichierCodage, "%u", &taille);

	if(fichierCodage != NULL)
		fclose(fichierCodage);

	return ((int)taille);
}//Fin lire_taille_codage()

int lire_codage_prufer(CodagePrufer *codage, char *nomFichier){
	if(codage == NULL){
		fprintf(stderr, "Pointeur vers codage vaut NULL\n");
		return -1;
	}
	if(codage->suitePrufer == NULL){
		fprintf(stderr, "Pointeur vers la suite de Prüfer vaut NULL\n");
		return -2;
	}
	if(nomFichier == NULL){
		fprintf(stderr, "Pointeur vers nomFichier vaut NULL\n");
		return -3;
	}

	FILE* fichier = fopen(nomFichier, "r");
	if(fichier == NULL)
		return -4;

	int nombreLu;

	unsigned int tailleCodage;

	fscanf(fichier, "%u\n", &tailleCodage);

	for(unsigned int i = 0; i < tailleCodage; i++){
		fscanf(fichier, "%d ", &nombreLu);
		codage->suitePrufer[i] = nombreLu;
	}//Fin for()

	if(fichier != NULL)
		fclose(fichier);

	return 0;
}//Fin lire_codage_prufer()

CodagePrufer* generer_codage_prufer(GRAPHE* arbre){
	if(arbre == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers le graphe vaut NULL.\n");
		return NULL;
	}
	if(arbre->premierSommet == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers le premier sommet du graphe vaut NULL.\n");
		return NULL;
	}
	if(arbre->nbS <= 2){
		fprintf(stderr, "** ERREUR : votre arbre contient moins de 3 sommets donc on ne peut PAS en trouver le codage de Prüfer.\n");
		return NULL;
	}

	//Un codage de Prüfer contient tjrs #V - 2 éléments.
	CodagePrufer* nvCodage = creer_codage_prufer(arbre->nbS - 2);
	if(nvCodage == NULL){
		fprintf(stderr, "** ERREUR à la création de la structure du codage de Prüfer.\n");
		return NULL;
	}

	unsigned int indiceCodage = 0;
	int resultatSupprimerSommet;
	SOMMET* plusPetitLabel;

	while(arbre->nbS > 2){

		//On récupére le sommet qui a le plus petit label.
		plusPetitLabel = arbre->premierSommet;
		//On le met dans la suite de Prüfer le seul sommet qui lui adjacent.
		nvCodage->suitePrufer[indiceCodage] = plusPetitLabel->adj->dest;

		indiceCodage++;

		//On supprime le sommet de plus petit label;
		resultatSupprimerSommet = supprimerSommet(arbre, plusPetitLabel->label);
		if(resultatSupprimerSommet < 0){
			fprintf(stderr, "** ERREUR lors de la suppression d'un sommet de l'arbre.\n");
			detruire_codage_prufer(nvCodage);
			return NULL;
		}
	}//Fin while()

	return nvCodage;
}//Fin generer_codage_prufer()
