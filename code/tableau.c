#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tableau.h"

struct Tableau_t{
	int* donnees;
	unsigned int taille;
	unsigned int dernierElementUtilise;
};

Tableau* creer_tableau(void){

	Tableau* nouveauTableau = malloc(sizeof(Tableau));
	if(nouveauTableau == NULL){
		return NULL;
	}

	nouveauTableau->taille = 2;

	nouveauTableau->donnees = malloc(sizeof(int) * nouveauTableau->taille);
	if(nouveauTableau->donnees == NULL){
		if(nouveauTableau != NULL){
			free(nouveauTableau);
		}
		return NULL;
	}

	nouveauTableau->dernierElementUtilise = 0;

	return nouveauTableau;
}//Fin nouveauTableau()

void afficher_tableau(Tableau* tab){
	if(tab == NULL)
		return;
	if(tab->donnees == NULL)
		return;

	if(tab->dernierElementUtilise == 0){
		printf("Le tableau est vide.\n");
		return;
	}

	for(size_t i = 0; i < tab->dernierElementUtilise; i++){
		printf("%d ", tab->donnees[i]);
	}
	printf("\n");
}//Fin afficher_tableau()

int modifier_taille_tableau(Tableau* tab, unsigned int nouvelleTaille){
	if(tab == NULL)
		return -1;
	if(tab->donnees == NULL)
		return -2;

	if(nouvelleTaille < tab->taille){
		fprintf(stderr, "** ERREUR : Vous essayez de réallouer un tableau à une plus petite taille ce qui conduit à la perte de certaine données.\n");
		fprintf(stderr, "Opération annulée.\n\n");
		return -3;
	}
	if(nouvelleTaille == tab->taille){
		fprintf(stderr, "** ATTENTION : Vous essayez de reallouer le tableau avec la même taille.\n");
		fprintf(stderr, "Pour économiser le temps processeur, opération refusée.\n\n");
		return -4;
	}

	int* nvTab = realloc(tab->donnees, sizeof(int) * nouvelleTaille);
	if(nvTab != NULL){ //Realloc a fonctionné.
		tab->taille = nouvelleTaille;
		tab->donnees = nvTab;
		nvTab = NULL;
		return 0;
	}else{ //Realloc n'a pas fonctionné.
		fprintf(stderr, "** ERREUR : L'opération de réallocation du tableau a échoué.\n");
		return -5;
	}
}//Fin modifier_taille_tableau()

int ajouter_element_tab(Tableau* tab, int element){
	if(tab == NULL){
		return -1;
	}
	if(tab->donnees == NULL)
		return -2;

	if(tab->dernierElementUtilise + 1 >= tab->taille){
		modifier_taille_tableau(tab, tab->taille * FACTEUR_REALLOC);
		tab->taille*=FACTEUR_REALLOC;
	}

	tab->donnees[tab->dernierElementUtilise] = element;
	tab->dernierElementUtilise+=1;

	return 0;
}//Fin ajouter_element_tab()

static int decalage_gauche_tab(Tableau* tab, size_t position){
	if(tab == NULL)
		return -1;
	if(tab->donnees == NULL)
		return -2;

	for(size_t i = position; i < tab->dernierElementUtilise - 1; i++){
		tab->donnees[i] = tab->donnees[i + 1];
	}

	return 0;
}//Fin decalage_gauche_tab()

int supprimer_element_tab(Tableau* tab, int element){
	if(tab == NULL)
		return -1;
	if(tab->donnees == NULL)
		return -2;

	for(unsigned int i = 0; i < tab->dernierElementUtilise; i++){
		if(tab->donnees[i] == element){
			tab->donnees[i] = 0;
			int resultatDecalage = decalage_gauche_tab(tab, i);
			if(resultatDecalage < 0){
				fprintf(stderr, "** ERREUR : L'opération de décalage a échoué.\n");
				return -3;
			}//Fin if()
			i-=1;
			tab->dernierElementUtilise-=1;
		}//Fin if()
	}//Fin for()

	return 0;
}//Fin supprimer_element_tab()

void detruire_tableau(Tableau* tab){
	if(tab != NULL){
		if(tab->donnees != NULL){
			free(tab->donnees);
		}
		free(tab);
	}
}//Fin supprimerTableau()
