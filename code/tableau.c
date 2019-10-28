#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tableau.h"

struct Tableau_t{
	int* donnees; //Le tableau de données.
	unsigned int taille; //La taille en mémoire du tableau.
	unsigned int dernierElementUtilise; //L'indice du dernier élément utilisé.
};

Tableau* creer_tableau(void){

	Tableau* nouveauTableau = malloc(sizeof(Tableau));
	if(nouveauTableau == NULL){
		fprintf(stderr, "** ERREUR lors de l'allocation de la structure.\n");
		return NULL;
	}

	nouveauTableau->taille = 2;

	nouveauTableau->donnees = malloc(sizeof(int) * nouveauTableau->taille);
	if(nouveauTableau->donnees == NULL){
		fprintf(stderr, "** ERREUR lors de l'allocation du tableau qui va contenir les données.\n");

		if(nouveauTableau != NULL)
			free(nouveauTableau);

		return NULL;
	}

	nouveauTableau->dernierElementUtilise = 0;

	return nouveauTableau;
}//Fin nouveauTableau()

void afficher_tableau(Tableau* tab){
	if(tab == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers tab dans affciher_tableau vaut NULL.\n");
		return;
	}
	if(tab->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données dans afficher_tableau vaut NULL.\n");
		return;
	}

	if(tab->dernierElementUtilise == 0){
		printf("Le tableau est vide.\n");
		return;
	}

	for(size_t i = 0; i < tab->dernierElementUtilise; i++){
		printf("%d ", tab->donnees[i]);
	}
	printf("\n");

	return;
}//Fin afficher_tableau()

int modifier_taille_tableau(Tableau* tab, unsigned int nouvelleTaille){
	if(tab == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers tab dans affciher_tableau vaut NULL.\n");
		return -1;
	}
	if(tab->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données dans afficher_tableau vaut NULL.\n");
		return -2;
	}

	//Realloc a une taille plus petite.
	if(nouvelleTaille < tab->taille){
		fprintf(stderr, "** ERREUR : Vous essayez de réallouer un tableau à une plus petite taille ce qui conduit à la perte de certaine données.\n");
		fprintf(stderr, "Opération annulée.\n\n");
		return -3;
	}

	//Realloc a la même taille.
	if(nouvelleTaille == tab->taille){
		fprintf(stderr, "** ATTENTION : Vous essayez de reallouer le tableau avec la même taille.\n");
		fprintf(stderr, "Pour économiser le temps processeur, opération refusée.\n\n");
		return -4;
	}

	//Realloc dans un pointeur temporaire car si échec de la réallocation, on ne veut pas perdre le pointeur vers les données.
	int* nvTab = realloc(tab->donnees, sizeof(int) * nouvelleTaille);
	if(nvTab != NULL){ //Realloc a fonctionné.
		tab->taille = nouvelleTaille;
		tab->donnees = nvTab;
		return 0;
	}else{ //Realloc n'a pas fonctionné.
		fprintf(stderr, "** ERREUR : L'opération de réallocation du tableau a échoué.\n");
		return -5;
	}
}//Fin modifier_taille_tableau()

int ajouter_element_tab(Tableau* tab, int element){
	if(tab == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers tab dans affciher_tableau vaut NULL.\n");
		return -1;
	}
	if(tab->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données dans afficher_tableau vaut NULL.\n");
		return -2;
	}

	//Si nécessaire, on agrandit la taille du tableau.
	if(tab->dernierElementUtilise + 1 >= tab->taille){
		int resultatRealloc = modifier_taille_tableau(tab, tab->taille * FACTEUR_REALLOC);
		if(resultatRealloc < 0){
			fprintf(stderr, "** ERREUR : La réallocation a échouée.\n");
			return -3;
		}
		//tab->taille*=FACTEUR_REALLOC;
	}

	//On ajoute l'élément.
	tab->donnees[tab->dernierElementUtilise] = element;
	tab->dernierElementUtilise+=1;

	return 0;
}//Fin ajouter_element_tab()

static int decalage_gauche_tab(Tableau* tab, size_t position){
	if(tab == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers tab dans affciher_tableau vaut NULL.\n");
		return -1;
	}
	if(tab->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données dans afficher_tableau vaut NULL.\n");
		return -2;
	}

	//On décale tout les éléments situés après l'indice 'position' d'une position vers la gauche.
	for(size_t i = position; i < tab->dernierElementUtilise - 1; i++){
		tab->donnees[i] = tab->donnees[i + 1];
	}

	return 0;
}//Fin decalage_gauche_tab()

int supprimer_element_tab(Tableau* tab, int element){
	if(tab == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers tab dans affciher_tableau vaut NULL.\n");
		return -1;
	}
	if(tab->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données dans afficher_tableau vaut NULL.\n");
		return -2;
	}

	//On supprime toutes les occurrences de element.
	for(unsigned int i = 0; i < tab->dernierElementUtilise; i++){
		if(tab->donnees[i] == element){
			tab->donnees[i] = 0;
			//On décale de 1 position vers la gauche tout les éléments situés après l'élément qu'on souhaite supprimer.
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
