/* ------------------------------------------------------------------------- *
 * Header qui contient les différentes structures nécessaires à la
 * représentation d'un graphe et les prototypes des fonctions pour manipuler
 * un graphe et obtenir certaines informations sur le graphe.
 * ------------------------------------------------------------------------- */

#ifndef GRAPHES_H
#define GRAPHES_H

#include "tableau.h"

#define MAX 100000

struct eltadj{ //Liste d'adjacence -- Sommet adjacent à un somme donné.
	int dest; //Extrémité de l'arc.
	int info; //Quelconque info - poids par exemple.
	struct eltadj *suivant; //Sommet adjacent suivant.
};

struct sommet{ //Un sommet du graphe.
  int label; //Indice du sommet.
	int info; //Info propre à un sommet. ie : Déjà visité ou couleur.
	struct sommet *suivant; //Sommet suivant dans la liste de tout les sommets.
	struct eltadj *adj; //Sommets adjacents à un sommet donné.
};

struct graphe{
	int nbS; //Nombre de sommets dans le graphe.
	int nbA; //Nombre d'arcs dans le graphe.
	int maxS; //Indice max attribué à un sommet.
	struct sommet *premierSommet; //Pt vers le premier sommet de la liste de sommets.
	struct sommet *dernierSommet; //Pt vers le dernier sommet de la liste de sommets.
};

typedef struct graphe GRAPHE;
typedef struct sommet SOMMET;
typedef struct eltadj ELTADJ;

void initialiserGraphe(GRAPHE *);

int ajouterSommet(GRAPHE *, int info);

int ajouterArc(GRAPHE *, int a, int b, int info);

int supprimerSommet(GRAPHE *, int label);

int supprimerArc(GRAPHE *, int a, int b);

void supprimerGraphe(GRAPHE *);

void afficherGraphe(GRAPHE *);

int lireFichier(char *nomf, GRAPHE *);

/* ------------------------------------------------------------------------- *
 ** Fonction pour sauvegarder un graphe (sa matrice d'adjacence) dans un fichier.
 *
 ** PARAMETRES
 * g, le graphe à sauvegarder.
 *
 ** RETOUR
 * 0, graphe sauvegardé dans le fichier "output_graph.txt".
 * -1, pointeur g vaut NULL.
 * -2, le premierSommet (structure) vaut NULL.
 * -3, impossible d'ouvrir le fichier ou il faut sauvegarder le graphe.
 * ------------------------------------------------------------------------- */
int sauvegarder_graphe(GRAPHE *g);

/* ------------------------------------------------------------------------- *
 ** Fonction pour obtenir le sommet d'un graphe.
 *
 ** PARAMETRES
 * g, le graphe.
 * labelSommet, le label du sommet qu'on veut obtenir.
 *
 ** RETOUR
 * Pointeur vers le sommet de label labelSommet.
 * NULL si le sommmet n'existe pas ou erreur.
 *
 * ------------------------------------------------------------------------- */
SOMMET* obtenir_sommet(GRAPHE* g, int labelSommet);

/* ------------------------------------------------------------------------- *
 ** Fonction pour obtenir la liste qui contient les voisins d'un sommet.
 *
 ** PARAMETRES
 * g, le graphe.
 * labelSommet, le label du sommet dont on veut obtenir la liste des sommets adjacents.
 *
 ** RETOUR
 * Pointeur vers le sommet de label labelSommet.
 * NULL si le sommmet n'existe pas ou erreur.
 *
 * ------------------------------------------------------------------------- */
ELTADJ* obtenir_voisin(GRAPHE* g, int labelSommet);

/* ------------------------------------------------------------------------- *
 ** Fonction pour obtenir les voisins d'un sommet.
 *
 ** PARAMETRES
 * g, le graphe.
 * labelSommet, le label du sommet dont on veut obtenir les voisins.
 *
 ** RETOUR
 * Un tableau contenant les voisins du sommet 'labelSommet'.
 * NULL sinon.
 * ------------------------------------------------------------------------- */
Tableau* obtenir_voisins_sommet(GRAPHE* g, int labelSommet);

/* ------------------------------------------------------------------------- *
 ** Fonction pour obtenir les sommets d'un graphe.
 *
 ** PARAMETRES
 * g, le graphe.
 *
 ** RETOUR
 * Un tableau contenant les sommets du graphe.
 * NULL sinon.
 * ------------------------------------------------------------------------- */
Tableau* obtenir_sommet_graphe(GRAPHE* g);

/* ------------------------------------------------------------------------- *
 ** Fonction pour tester la connexité d'un graphe.
 *
 ** PARAMETRES
 * g, le graphe dont on doit vérifier la connexité.
 *
 ** RETOUR
 * true si le graphe est connexe.
 * false si le graphe n'est pas connexe ou erreur.
 * ------------------------------------------------------------------------- */
bool test_connexite(GRAPHE* g);

/* ------------------------------------------------------------------------- *
 ** Fonction pour déterminer si un graphe contient un cycle
 * (cette fonction modifie le graphe de départ).
 *
 ** PARAMETRES
 * g, un pointeur vers le graphe étudié.
 *
 ** RETOUR
 * true si le graphe contient un cycle ou erreur.
 * false si le graphe ne contient pas de cycle.
 * ------------------------------------------------------------------------- */
bool contient_cycle(GRAPHE *g);

/* ------------------------------------------------------------------------- *
 ** Fonction pour déterminer si un graphe est non oriente
 * (cette fonction modifie le graphe de départ)
 * 
 ** PARAMETRES
 * g, un pointeur vers le graphe étudié.
 *
 ** RETOUR
 * true si le graphe est non oriente.
 * false si le graphe est n'est pas non oriente ou erreur.
 * ------------------------------------------------------------------------- */
bool est_non_oriente(GRAPHE *g);

#endif
