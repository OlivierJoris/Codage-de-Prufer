#ifndef GRAPHES_H
#define GRAPHES_H

#define MAX 10000

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

#endif