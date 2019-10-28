#ifndef __TABLEAU__
#define __TABLEAU__

//Constante multiplicative pour la réallocation du tableau.
#define FACTEUR_REALLOC 2

//Type opaque Tableau.
typedef struct Tableau_t Tableau;

/*******************************
** Fonction pour créer un Tableau.
*
** Paramètre :
* taille, la taille souhaitée du tableau.
*
** Retour :
* Un pointeur vers un Tableau. NULL sinon.
*
*********************************/
Tableau* creer_tableau(void);

/*******************************
** Fonction pour afficher un Tableau.
*
** Paramètre :
* tab, le Tableau à afficher.
*
** Retour :
* /
*
*********************************/
void afficher_tableau(Tableau* tab);

/*******************************
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
* -4, tentative de réallocation a une même taille. Refusé pour économiser le temps processeur.
* -5, la réallocation (realloc) a échoué.
*
*********************************/
int modifier_taille_tableau(Tableau* tab, unsigned int nouvelleTaille);

/*******************************
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
*********************************/
int ajouter_element_tab(Tableau* tab, int element);

/*******************************
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
*********************************/
int supprimer_element_tab(Tableau* tab, int element);

/*******************************
** Fonction pour supprimer un tableau.
*
** Paramètre :
* tab, le Tableau à supprimer.
*
** Retour :
* /
*
*********************************/
void detruire_tableau(Tableau* tab);
#endif
