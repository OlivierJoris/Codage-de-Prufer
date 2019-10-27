#ifndef __TABLEAU__
#define __TABLEAU__

#define FACTEUR_REALLOC 2

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
* /
*
*********************************/
int modifier_taille_tableau(Tableau* tab, unsigned int nouvelleTaille);

int ajouter_element_tab(Tableau* tab, int element);

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
