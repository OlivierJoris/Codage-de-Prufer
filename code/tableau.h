#ifndef __TABLEAU__
#define __TABLEAU__

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
Tableau* creer_tableau(unsigned int taille);

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
void modifier_taille_tableau(Tableau* tab, unsigned int nouvelleTaille);

/*******************************
** Fonction pour modifier une valeur contenue dans un Tableau.
*
** Paramètres :
* tab, le Tableau dont il faut modifier un élément.
* position, la position de l'élément à modifier dans le Tableau.
* nouvelleValeur, la valeur à attribuer à l'élément qui se trouve en position position.
*
** Retour :
* /
*
*********************************/
void modifier_valeur_tableau(Tableau* tab, unsigned int position, int nouvelleValeur);

/*******************************
** Fonction pour incrémenter la valeur d'un élément du Tableau.
*
** Paramètres :
* tab, le Tableau dont il faut modifier un élément.
* position, la position de l'élément à modifier dans le Tableau.
*
** Retour :
* /
*
*********************************/
void incrementer_valeur_tableau(Tableau* tab, unsigned int position);

/*******************************
** Fonction pour décrémenter la valeur d'un élément du Tableau.
*
** Paramètres :
* tab, le Tableau dont il faut modifier un élément.
* position, la position de l'élément à modifier dans le Tableau.
*
** Retour :
* /
*
*********************************/
void decrementer_valeur_tableau(Tableau* tab, unsigned int position);

/*******************************
** Fonction pour récupérer la valeur d'un élément dans le Tableau.
*
** Paramètres :
* tab, le Tableau dont il faut récupérer un élément.
* position, la position de l'élément à récupérer dans le Tableau..
*
** Retour :
* L'élément qui se trouve à la position 'position' dans le Tableau.
*
*********************************/
int recuperer_valeur_tableau(Tableau* tab, unsigned int position);

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
void supprimerTableau(Tableau* tab);
#endif
