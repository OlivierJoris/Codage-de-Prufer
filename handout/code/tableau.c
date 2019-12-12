/* ------------------------------------------------------------------------- *
 * Fichier qui contient les fonctions pour manipuler un tableau de nombres.
 * ------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "tableau.h"

/*** PROTOTYPES DES FONCTIONS STATIC ***/


/* ------------------------------------------------------------------------- *
** Fonction pour modifier la taille d'un Tableau.
*
** Paramètres :
* tab, le Tableau dont il faut modifier la taille.
* nouvelleTaille, la nouvelle taille souhaitée pour le Tableau.
*
** Retour :
* 0, la taille a bien été modifiée.
* -1, pointeur tab vaut NULL.
* -2, pointeur vers les données dans la structure Tableau vaut NULL.
* -3, tentative de réallocation a une taille plus petite. Refusé car conduit a la perte de certaines données.
* -4, la réallocation (realloc) a échoué.
*
* ------------------------------------------------------------------------- */
static int modifier_taille_tableau(Tableau* tab, unsigned int nouvelleTaille);

/* ------------------------------------------------------------------------- *
** Fonction qui permet de décaler les éléments situés à partir de position
* d'une position vers la gauche.
*
** Paramètres :
* tab, le Tableau dans lequel on doit effectuer le decalage.
* position, position à partir de laquelle on doit décaler les éléments.
*
** Retour :
* 0, décalage effectué sans problèmes.
* -1, pointeur tab vaut NULL.
* -2, pointeur vers les données dans la structure Tableau vaut NULL.
*
* ------------------------------------------------------------------------- */
static int decalage_gauche_tab(Tableau* tab, size_t position);

/* ------------------------------------------------------------------------- *
** Fonction qui vérifie si un tableau est trié.
*
** Paramètres :
* tab, le Tableau dont on doit vérifier s'il est trié ou pas.
*
** Retour :
* true, le tableau tab est trié.
* false, le tableau n'est pas trié ou erreur.
*
* ------------------------------------------------------------------------- */
static bool tableau_est_trie(Tableau* tab);

/* ------------------------------------------------------------------------- *
** Fonction pour comparer 2 éléments du tableau.
* Nécessaire pour le quicksort implémenté dans la librairie standard (stdlib.h).
*
** Paramètres :
* firstValue, pointeur vers un élément du tableau.
* secondValue, pointeur vers l'élément suivant dans le tableau.
*
** Retour :
* Différence entre les 2.
*
* ------------------------------------------------------------------------- */
static int compare_values(const void* firstValue, const void* secondValue);

/* ------------------------------------------------------------------------- *
** Fonction qui trie un tableau à l'aide du quicksort implémenté dans la
* librairie standard.
*
** Paramètres :
* tab, le Tableau à trier.
*
** Retour :
* 0, le tableau a été trié ou était déjà trié.
* -1, pointeur tab vaut NULL.
* -2, pointeur vers les données dans la structure Tableau vaut NULL.
*
* ------------------------------------------------------------------------- */
static int tri_tableau(Tableau* tab);


/*** IMPLEMENTATIONS DES FONCTIONS ***/


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

	nouveauTableau->nbreElements = 0;

	return nouveauTableau;
}//Fin nouveauTableau()

void afficher_tableau(Tableau* tab){
	if(tab == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers tab dans afficher_tableau vaut NULL.\n");
		return;
	}
	if(tab->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données dans afficher_tableau vaut NULL.\n");
		return;
	}

	if(tab->nbreElements == 0){
		printf("Le tableau est vide.\n");
		return;
	}

	for(size_t i = 0; i < tab->nbreElements; i++){
		printf("%d ", tab->donnees[i]);
	}
	printf("\n");

	return;
}//Fin afficher_tableau()

static int modifier_taille_tableau(Tableau* tab, unsigned int nouvelleTaille){
	if(tab == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers tab dans modifier_taille_tableau vaut NULL.\n");
		return -1;
	}
	if(tab->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données dans modifier_taille_tableau vaut NULL.\n");
		return -2;
	}

	//Realloc a une taille plus petite.
	if(nouvelleTaille < tab->taille){
		fprintf(stderr, "** ERREUR : Vous essayez de réallouer un tableau à une plus petite taille ce qui conduit à la perte de certaine données.\n");
		fprintf(stderr, "Opération annulée.\n\n");
		return -3;
	}

	//Realloc dans un pointeur temporaire car si échec de la réallocation, on ne veut pas perdre le pointeur vers les données.
	int* nvTab = realloc(tab->donnees, sizeof(int) * nouvelleTaille);
	if(nvTab != NULL){ //Realloc a fonctionné.
		tab->taille = nouvelleTaille;
		tab->donnees = nvTab;
		return 0;
	}else{ //Realloc n'a pas fonctionné.
		fprintf(stderr, "** ERREUR : L'opération de réallocation du tableau a échoué.\n");
		return -4;
	}
}//Fin modifier_taille_tableau()

int ajouter_element_tab(Tableau* tab, int element){
	if(tab == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers tab dans ajouter_element_tab vaut NULL.\n");
		return -1;
	}
	if(tab->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données dans ajouter_element_tab vaut NULL.\n");
		return -2;
	}

	//Si nécessaire, on agrandit la taille du tableau.
	if(tab->nbreElements + 1 >= tab->taille){
		int resultatRealloc = modifier_taille_tableau(tab, tab->taille * FACTEUR_REALLOC);
		if(resultatRealloc < 0){
			fprintf(stderr, "** ERREUR : La réallocation a échouée.\n");
			return -3;
		}
	}

	//On ajoute l'élément.
	tab->donnees[tab->nbreElements] = element;
	tab->nbreElements+=1;

	return 0;
}//Fin ajouter_element_tab()

static int decalage_gauche_tab(Tableau* tab, size_t position){
	if(tab == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers tab dans decalage_gauche_tab vaut NULL.\n");
		return -1;
	}
	if(tab->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données dans decalage_gauche_tab vaut NULL.\n");
		return -2;
	}

	//On décale tout les éléments situés après l'indice 'position' d'une position vers la gauche.
	for(size_t i = position; i < tab->nbreElements - 1; i++){
		tab->donnees[i] = tab->donnees[i + 1];
	}

	return 0;
}//Fin decalage_gauche_tab()

int supprimer_element_tab(Tableau* tab, int element){
	if(tab == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers tab dans supprimer_element_tab vaut NULL.\n");
		return -1;
	}
	if(tab->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données dans supprimer_element_tab vaut NULL.\n");
		return -2;
	}

	//On supprime toutes les occurrences de element.
	for(unsigned int i = 0; i < tab->nbreElements; i++){
		if(tab->donnees[i] == element){
			tab->donnees[i] = 0;
			//On décale de 1 position vers la gauche tout les éléments situés après l'élément qu'on souhaite supprimer.
			int resultatDecalage = decalage_gauche_tab(tab, i);
			if(resultatDecalage < 0){
				fprintf(stderr, "** ERREUR : L'opération de décalage a échoué.\n");
				return -3;
			}//Fin if()
			i-=1;
			tab->nbreElements-=1;
		}//Fin if()
	}//Fin for()

	return 0;
}//Fin supprimer_element_tab()

int copier_tableau(Tableau* source, Tableau* destination){
	if(source == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers source dans copier_tableau vaut NULL.\n");
		return -1;
	}
	if(source->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données du tableau source dans copier_tableau vaut NULL.\n");
		return -2;
	}
	if(destination == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers destination dans copier_tableau vaut NULL.\n");
		return -3;
	}
	if(destination->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données du tableau destination dans copier_tableau vaut NULL.\n");
		return -4;
	}

	//Met l'ensemble des éléments de destination à 0.
	for(size_t i = 0; i < destination->nbreElements; i++)
		destination->donnees[i] = 0;

	//Permet d'ajouter des éléments au début du tableau de destination.
	destination->nbreElements = 0;

	int resultatAjout;

	//On met tous les éléments de source dans destination.
	for(size_t i = 0; i < source->nbreElements; i++){
		resultatAjout = ajouter_element_tab(destination, source->donnees[i]);
		if(resultatAjout < 0){
			fprintf(stderr, "** ERREUR lors de l'ajout d'un élément à destination dans copier_tableau.\n");
			return -5;
		}
	}//Fin for()

	return 0;
}//Fin copier_tableau()

static bool tableau_est_trie(Tableau* tab){
	if(tab == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers tab dans tableau_est_trie vaut NULL.\n");
		return false;
	}
	if(tab->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données dans tableau_est_trie vaut NULL.\n");
		return false;
	}

	for(size_t i = 0; i < tab->nbreElements - 1; i++){
		//Si élément en i n'est pas <= à l'élément en i + 1 alors le tableau n'est pas trié.
		if(tab->donnees[i] > tab->donnees[i + 1])
			return false;
	}

	return true;
}//Fin tableau_est_trie()

static int compare_values(const void* firstValue, const void* secondValue){
	return ( *(int*)firstValue - *(int*)secondValue);
}//Fin compare_values()

static int tri_tableau(Tableau* tab){
	if(tab == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers tab dans tri_tableau vaut NULL.\n");
		return -1;
	}
	if(tab->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données dans tri_tableau vaut NULL.\n");
		return -2;
	}

	qsort(tab->donnees, tab->nbreElements, sizeof(int), compare_values);

	return 0;
}//Fin tri_tableau()

Tableau* union_tab(Tableau* tab1, Tableau* tab2){
	if(tab1 == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers tab1 dans union_tab vaut NULL.\n");
		return NULL;
	}
	if(tab1->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données de tab1 dans union_tab vaut NULL.\n");
		return NULL;
	}
	if(tab2 == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers tab2 dans union_tab vaut NULL.\n");
		return NULL;
	}
	if(tab2->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données dans union_tab vaut NULL.\n");
		return NULL;
	}

	//On crée le tableau qui va contenir l'union de tab1 et tab2.
	Tableau* tabUnion = creer_tableau();
	if(tabUnion == NULL){
		fprintf(stderr, "** ERREUR à la création de tabUnion dans union_tab.\n");
		return NULL;
	}

	//Si les 2 tableaux on une taille de 0, on retourne la tableau vide.
	if(tab1->nbreElements == 0 && tab2->nbreElements == 0)
		return tabUnion;

	//Si un des 2 tableaux a une taille nulle. On retourne la copie de l'autre.

	//Le tab1 est vide donc on retourne la copie de tab2.
	if(tab1->nbreElements == 0){
		int resultatCopie = copier_tableau(tab2, tabUnion);
		if(resultatCopie < 0){
			fprintf(stderr, "** ERREUR lors de la copie d'un tableau dans union_tab.\n");
			detruire_tableau(tabUnion);
			return NULL;
		}
		return tabUnion;
	}else{
		//Le tab2 est vide donc on retourne la copie de tab1.
		if(tab2->nbreElements == 0){
			int resultatCopie = copier_tableau(tab1, tabUnion);
			if(resultatCopie < 0){
				fprintf(stderr, "** ERREUR lors de la copie d'un tableau dans union_tab.\n");
				detruire_tableau(tabUnion);
				return NULL;
			}
			return tabUnion;
		}
	}//Fin else


	//On sait que la taille max de l'union est donné par le nbre d'éléments dans tab1 + nbre d'éléments dans tab2.
	int resultatModifTailleUnion = modifier_taille_tableau(tabUnion, tab1->nbreElements + tab2->nbreElements);
	if(resultatModifTailleUnion < 0){
		fprintf(stderr, "** ERREUR lors de la modification de la taille de tabUnion dans union_tab.\n");
		detruire_tableau(tabUnion);
		return NULL;
	}

	//On vérifie si les 2 tableaux sont triés par ordre croissant avant de réaliser l'union des 2.
	bool tab1Trie = tableau_est_trie(tab1);
	bool tab2Trie = tableau_est_trie(tab2);

	//S'ils ne sont pas triés, on les trie.
	if(!tab1Trie){
		int resultatTri1 = tri_tableau(tab1);
		if(resultatTri1 < 0){
			fprintf(stderr, "** ERREUR lors du tri de tab1 dans union_tab\n");
			detruire_tableau(tabUnion);
			return NULL;
		}
	}
	if(!tab2Trie){
		int resultatTri2 = tri_tableau(tab2);
		if(resultatTri2 < 0){
			fprintf(stderr, "** ERREUR lors du tri de tab2 dans union_tab\n");
			detruire_tableau(tabUnion);
			return NULL;
		}
	}

	//On parcourt les 2 tableaux simultanément avec un indice de parcours pour chaque tableau.
	//A chaque tour de boucle, on compare les 2 éléments dans les tableaux aux indices reespectifs.
	//On ajoute le plus petit à l'union et on incrémente les indices de parcours en fonction de l'élément ajouté.
	unsigned int posTab1 = 0, posTab2 = 0;
	int resultatAJout;

	//Tant qu'on arrive pas à la fin d'un des 2 tableaux.
	while(posTab1 <= tab1->nbreElements - 1 && posTab2 <= tab2->nbreElements - 1){

		//Si l'élément est le même dans les 2 tabs, on ajoute à l'union et on incrémente les 2 indices de parcours.
		if(tab1->donnees[posTab1] == tab2->donnees[posTab2]){
			resultatAJout = ajouter_element_tab(tabUnion, tab1->donnees[posTab1]);
			if(resultatAJout < 0){
				fprintf(stderr, "** ERREUR lors de l'ajout d'un élément dans union_tab.\n");
				detruire_tableau(tabUnion);
				return NULL;
			}
			posTab1++;
			posTab2++;
		}else{
			//Si tab1[posTab1] < tab2[posTab2]. Alors, on ajoute tab1[posTab1] à l'union et on incrémente posTab1.
			if(tab1->donnees[posTab1] < tab2->donnees[posTab2]){
				resultatAJout = ajouter_element_tab(tabUnion, tab1->donnees[posTab1]);
				if(resultatAJout < 0){
					fprintf(stderr, "** ERREUR lors de l'ajout d'un élément dans union_tab.\n");
					detruire_tableau(tabUnion);
					return NULL;
				}
				posTab1++;
			}else{
				//Si tab2[posTab2] < tab1[posTab1]. Alors, on ajoute tab2[posTab2] à l'union et on incrémente tab2.
				if(tab2->donnees[posTab2] < tab1->donnees[posTab1]){
					resultatAJout = ajouter_element_tab(tabUnion, tab2->donnees[posTab2]);
					if(resultatAJout < 0){
						fprintf(stderr, "** ERREUR lors de l'ajout d'un élément dans union_tab.\n");
						detruire_tableau(tabUnion);
						return NULL;
					}
					posTab2++;
				}
			}
		}//Fin if()
	}//Fin while()

	//Quand on arrive ici, on est arrivé à la fin d'un tableau ou des deux.
	//S'ils n'ont pas la même taille, on ajoute les éléments restants.
	//On ajoute les éléments restants (s'il en reste) du premier tab.
	if(posTab1 <= tab1->nbreElements - 1){
		for(size_t i = posTab1; i <= tab1->nbreElements - 1; i++){
			resultatAJout = ajouter_element_tab(tabUnion, tab1->donnees[i]);
			if(resultatAJout < 0){
				fprintf(stderr, "** ERREUR lors de l'ajout d'un élément dans union_tab.\n");
				detruire_tableau(tabUnion);
				return NULL;
			}
		}//Fin for()
	}//Fin if()

	//On ajoute les élemnts restants (s'il en reste) du deuxième tab.
	if(posTab2 <= tab2->nbreElements - 1){
		for(size_t i = posTab2; i <= tab2->nbreElements - 1; i++){
			resultatAJout = ajouter_element_tab(tabUnion, tab2->donnees[i]);
			if(resultatAJout < 0){
				fprintf(stderr, "** ERREUR lors de l'ajout d'un élément dans union_tab.\n");
				detruire_tableau(tabUnion);
				return NULL;
			}
		}//Fin for()
	}//Fin if()

	return tabUnion;
}//Fin union_tab()

bool egalite_tableaux(Tableau* tab1, Tableau* tab2){
	if(tab1 == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers tab1 dans egalite_tableaux vaut NULL.\n");
		return NULL;
	}
	if(tab1->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données de tab1 dans egalite_tableaux vaut NULL.\n");
		return NULL;
	}
	if(tab2 == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers tab2 dans egalite_tableaux vaut NULL.\n");
		return NULL;
	}
	if(tab2->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données de tab2 dans egalite_tableaux vaut NULL.\n");
		return NULL;
	}

	//Si les tableaux ne contienent pas le même nombre d'éléments, on sait d'avance qu'ils ne sont pas égaux.
	if(tab1->nbreElements != tab2->nbreElements)
		return false;

	//On vérifie que les tableaux soit triés avant de vérifier s'ils sont égaux.
	bool tab1Trie = tableau_est_trie(tab1);
	bool tab2Trie = tableau_est_trie(tab2);

	//S'ils ne sont pas triés, on les trie.
	if(!tab1Trie){
		int resultatTri1 = tri_tableau(tab1);
		if(resultatTri1 < 0){
			fprintf(stderr, "** ERREUR lors du tri de tab1 dans egalite_tableaux\n");
			return NULL;
		}
	}

	if(!tab2Trie){
		int resultatTri2 = tri_tableau(tab2);
		if(resultatTri2 < 0){
			fprintf(stderr, "** ERREUR lors du tri de tab2 dans egalite_tableaux\n");
			return NULL;
		}
	}

	//On sait qu'ils ont la même taille donc on prend indifférement tab1->nbreElements ou tab2->nbreElements.
	//On parcourt les deux tableaux en même temps et on vérifie si les éléments sont égaux 2 à 2.
	for(size_t i = 0; i < tab1->nbreElements; i++){
		//Les éléments situés à un même index ont des valeurs différentes. Donc les tableaux ne sont pas égaux.
		if(tab1->donnees[i] != tab2->donnees[i])
			return false;
	}//Fin for()

	return true;
}//Fin egalite_tableaux()

int difference_tableaux(Tableau* tab1, Tableau* tab2){
	if(tab1 == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers tab1 dans difference_tableaux vaut NULL.\n");
		return -1;
	}
	if(tab1->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données de tab1 dans difference_tableaux vaut NULL.\n");
		return -2;
	}
	if(tab2 == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers tab2 dans difference_tableaux vaut NULL.\n");
		return -3;
	}
	if(tab2->donnees == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers les données de tab2 dans difference_tableaux vaut NULL.\n");
		return -4;
	}

	int resultatSuppression;

	//On retire de tab1 tout les éléments de tab2.
	for(size_t i = 0; i < tab2->nbreElements; i++){
		resultatSuppression = supprimer_element_tab(tab1, tab2->donnees[i]);
		if(resultatSuppression < 0){
			fprintf(stderr, "** ERREUR lors de la suppression d'un élément de tab1 dans difference_tableaux.\n");
			return -5;
		}
	}//Fin for()

	return 0;
}//Fin difference_tableaux()

void detruire_tableau(Tableau* tab){
	if(tab != NULL){
		if(tab->donnees != NULL){
			free(tab->donnees);
		}
		free(tab);
	}
}//Fin detruire_tableau()
