/* ------------------------------------------------------------------------- *
 * Fichier qui contient l'implémentation du type Tableau ainsi que les
 * prototypes des fonctions nécessaires à sa manipulation.
 * ------------------------------------------------------------------------- */

#ifndef __TABLEAU__
#define __TABLEAU__

#include <stdbool.h>

//Constante multiplicative pour la réallocation du tableau.
#define FACTEUR_REALLOC 2

//Type opaque Tableau.
typedef struct Tableau_t{
	int* donnees; //Le tableau de données.
	unsigned int taille; //La taille en mémoire du tableau.
	unsigned int nbreElements; //Nombre d'éléments présents dans le tableau.
}Tableau;

/* ------------------------------------------------------------------------- *
** Fonction pour créer un Tableau.
*
** Paramètre :
* taille, la taille souhaitée du tableau.
*
** Retour :
* Un pointeur vers un Tableau. NULL sinon.
*
* ------------------------------------------------------------------------- */
Tableau* creer_tableau(void);

/* ------------------------------------------------------------------------- *
** Fonction pour afficher un Tableau.
*
** Paramètre :
* tab, le Tableau à afficher.
*
** Retour :
* /
*
* ------------------------------------------------------------------------- */
void afficher_tableau(Tableau* tab);

/* ------------------------------------------------------------------------- *
** Fonction pour ajouter un élément au tableau.
*
** Paramètres :
* tab, le Tableau dans lequel il faut ajouter un élément.
* element, l'élément à ajouter.
*
** Retour :
* 0, l'élément a bien été ajouté.
* -1, pointeur tab vaut NULL.
* -2, pointeur vers les données dans la structure Tableau vaut NULL.
* -3, réallocation a échouée.
*
* ------------------------------------------------------------------------- */
int ajouter_element_tab(Tableau* tab, int element);

/* ------------------------------------------------------------------------- *
** Fonction pour supprimer toutes les occurrences d'un élément dans un tab.
*
** Paramètres :
* tab, le Tableau dans lequel il faut supprimer les occurrences de element.
* element, l'élément dont il faut supprimer toutes les occurrences.
*
** Retour :
* 0, toutes les occurrences de element ont bien été suprrimées.
* -1, pointeur tab vaut NULL.
* -2, pointeur vers les données dans la structure Tableau vaut NULL.
* -3, erreur lors du décalage des données au sein du tableau.
*
* ------------------------------------------------------------------------- */
int supprimer_element_tab(Tableau* tab, int element);

/* ------------------------------------------------------------------------- *
 ** Fonction pour copier un tableau dans un autre.
 *
 ** PARAMETRES
 * source, le tableau source.
 * destination, le tableau de destination.
 *
 ** RETOUR
 * 0, la copie s'est réalisé sans problème.
 * -1, pointeur source vaut NULL.
 * -2, pointeur vers les données de source dans la structure Tableau vaut NULL.
 * -3, pointeur destination vaut NULL.
 * -4, pointeur vers les données de destination dans la structure Tableau vaut NULL.
 * -5, erreur lors de l'ajout d'un élément à destination.
 *
 * ------------------------------------------------------------------------- */
int copier_tableau(Tableau* source, Tableau* destination);

/* ------------------------------------------------------------------------- *
** Fonction qui construit l'union de 2 tableaux.
* ATTENTION : Si un tableau contient des élements en double alors erreur.
*				Il faut que chaque élément soit unique.
*
** Paramètres :
* tab1, le premier tableau de l'union.
* tab2, le deuxième tableau de l'union.
*
** Retour :
* Pointeur vers un Tableau qui contient l'union de tab1 et tab2. NULL en cas d'erreur.
*
* ------------------------------------------------------------------------- */
Tableau* union_tab(Tableau* tab1, Tableau* tab2);

/* ------------------------------------------------------------------------- *
** Fonction qui teste l'égalité de 2 tableaux.
*
** Paramètres :
* tab1, le premier tableau.
* tab2, le deuxième tableau.
*
** Retour :
* true si les tableaux sont les mêmes.
* false si les tableaux ne sont pas les mêmes ou erreur.
*
* ------------------------------------------------------------------------- */
bool egalite_tableaux(Tableau* tab1, Tableau* tab2);

/* ------------------------------------------------------------------------- *
** Fonction qui réalise la différence de 2 tableaux.
* Les deux tableaux sont considérés commme des ensembles.
* Donc, on effectue l'opération tab1\tab2.
** ATTENTION : les éléments de tab1 sont modifiés par cette fonction.
*
** Paramètres :
* tab1, le premier tableau.
* tab2, le deuxième tableau.
*
** Retour :
* 0, la différence a été réalisée correctement.
* -1, pointeur tab1 vaut NULL.
* -2, pointeur vers les données dans la structure Tableau de tab1 vaut NULL.
* -3, pointeur tab2 vaut NULL.
* -4, pointeur vers les données dans la structure Tableau de tab2 vaut NULL.
* -5, problème lors de la suppression d'un élément de tab1.
*
* ------------------------------------------------------------------------- */
int difference_tableaux(Tableau* tab1, Tableau* tab2);

/* ------------------------------------------------------------------------- *
** Fonction pour supprimer un tableau.
*
** Paramètre :
* tab, le Tableau à supprimer.
*
** Retour :
* /
*
* ------------------------------------------------------------------------- */
void detruire_tableau(Tableau* tab);

#endif
