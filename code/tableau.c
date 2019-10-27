#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tableau.h"

struct Tableau_t{
	int* donnees;
	unsigned int taille;
};

Tableau* creer_tableau(unsigned int taille){

	Tableau* nouveauTableau = malloc(sizeof(Tableau));
	if(nouveauTableau == NULL){
		return NULL;
	}

	nouveauTableau->taille = taille;

	nouveauTableau->donnees = malloc(sizeof(int) * taille);
	if(nouveauTableau->donnees == NULL){
		if(nouveauTableau != NULL){
			free(nouveauTableau);
		}
		return NULL;
	}

	for(size_t i = 0; i < nouveauTableau->taille; i++){
		nouveauTableau->donnees[i] = 0;
	}

	return nouveauTableau;
}//Fin nouveauTableau()

void afficher_tableau(Tableau* tab){
	assert(tab != NULL);

	for(size_t i = 0; i < tab->taille; i++){
		printf("%d ", tab->donnees[i]);
	}
	printf("\n");
}//Fin afficher_tableau()

void modifier_taille_tableau(Tableau* tab, unsigned int nouvelleTaille){
	assert(tab != NULL && tab->donnees != NULL);

	if(nouvelleTaille < tab->taille){
		fprintf(stderr, "** ERREUR : Vous essayez de réallouer un tableau à une plus petite taille ce qui conduit à la perte de certaine données.\n");
		fprintf(stderr, "Opération annulée.\n\n");
		return;
	}
	if(nouvelleTaille == tab->taille){
		fprintf(stderr, "** ATTENTION : Vous essayez de reallouer le tableau avec la même taille.\n");
		fprintf(stderr, "Pour économiser le temps processeur, opération refusée.\n\n");
		return;
	}

	int* nvTab = realloc(tab->donnees, sizeof(int) * nouvelleTaille);
	if(nvTab != NULL){ //Realloc a fonctionné.
		tab->taille = nouvelleTaille;
		tab->donnees = nvTab;
		nvTab = NULL;
		return;
	}else{ //Realloc n'a pas fonctionné.
		fprintf(stderr, "** ERREUR : L'opération de réallocation du tableau a échoué.\n");
		return;
	}
}//Fin modifier_taille_tableau()

void modifier_valeur_tableau(Tableau* tab, unsigned int position, int nouvelleValeur){
	assert(tab != NULL && tab->donnees != NULL);

	if(position > tab->taille - 1){
		fprintf(stderr, "** ERREUR : Le tableau a une taille %u et vous voulez modifier l'élément en position %u. IMPOSSIBLE !\n", tab->taille, position);
		return;
	}

	tab->donnees[position] = nouvelleValeur;

	return;
}//Fin modifier_valeur_tableau()

void incrementer_valeur_tableau(Tableau* tab, unsigned int position){
	assert(tab != NULL && tab->donnees != NULL);

	if(position > tab->taille - 1){
		fprintf(stderr, "** ERREUR : Le tableau a une taille %u et vous voulez modifier l'élément en position %u. IMPOSSIBLE !\n", tab->taille, position);
		return;
	}

	tab->donnees[position]++;

	return;
}//Fin incrementer_valeur_tableau()

void decrementer_valeur_tableau(Tableau* tab, unsigned int position){
	assert(tab != NULL && tab->donnees != NULL);

	if(position > tab->taille - 1){
		fprintf(stderr, "** ERREUR : Le tableau a une taille %u et vous voulez modifier l'élément en position %u. IMPOSSIBLE !\n", tab->taille, position);
		return;
	}

	tab->donnees[position]--;

	return;
}//Fin decrementer_valeur_tableau()

int recuperer_valeur_tableau(Tableau* tab, unsigned int position){
	assert(tab != NULL && tab->donnees != NULL);

	if(position > tab->taille - 1){
		fprintf(stderr, "** ERREUR : Le tableau a une taille %u et vous voulez récupérer l'élément en position %u. IMPOSSIBLE !\n", tab->taille, position);
		exit(-1);
	}

	return tab->donnees[position];
}//Fin recuperer_valeur_tableau()

void supprimerTableau(Tableau* tab){
	if(tab != NULL){
		if(tab->donnees != NULL){
			free(tab->donnees);
		}
		free(tab);
	}
}//Fin supprimerTableau()
