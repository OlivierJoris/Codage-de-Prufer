/* ------------------------------------------------------------------------- *
 * Header qui contient l'implémentation du type CodagePrufer et les
 * prototypes :
 * 	- des fonctions pour manipuler un codage de Prüfer;
 *	- de la fonction de codage;
 * 	- de la fonction de décodage.
 * ------------------------------------------------------------------------- */

#ifndef __PRUFER__
#define  __PRUFER__

#include "graphes.h"

//Structure qui représente un codage de Prüfer.
typedef struct CodagePrufer_t{
	unsigned int taille; //La taille du codage de Prüfer.
	int* suitePrufer; //La suite de Prüfer (suite de nombres).
}CodagePrufer;

/* ------------------------------------------------------------------------- *
 * Permet de créer un codage de Prüfer (allocation structure)
 *
 * PARAMETERS
 * taille    La taille de la suite de Prüfer.
 *
 * RETOUR
 * NULL, si erreur d'allocation.
 * Sinon, un pointeur vers la structure allouée.
 * ------------------------------------------------------------------------- */
CodagePrufer *creer_codage_prufer(unsigned int taille);

/* ------------------------------------------------------------------------- *
 * Permet de libérer la mémoire allouée à un codage de Prüfer.
 *
 * PARAMETERS
 * codage, pointeur vers la structure à détruire.
 *
 * RETOUR
 * /
 *
 * ------------------------------------------------------------------------- */
void detruire_codage_prufer(CodagePrufer *codage);

/* ------------------------------------------------------------------------- *
 * Procédure qui affiche un codage de Prüfer.
 *
 * PARAMETERS
 * codage, pointeur vers le codage à affciher.
 *
 * RETOUR
 * /
 *
 * ------------------------------------------------------------------------- */
void afficher_codage_prufer(CodagePrufer *codage);

/* ------------------------------------------------------------------------- *
 * Permet de lire la taille d'un codage enregistré dans un fichier.
 *
 * PARAMETERS
 * nomFichier, nom du fichier qui contient le codage.
 *
 * RETOUR
 * >0, la taille du codage qui se trouve dans le fichier 'nomFichier'.
 * -1, pointeur vers le nom du fichier non valide (= NULL).
 * -2, impossible d'ouvrir le fichier.
 *
 * ------------------------------------------------------------------------- */
int lire_taille_codage(char *nomFichier);

/* ------------------------------------------------------------------------- *
 * Permet de lire un codage situé dans un fichier.
 *
 * PARAMETERS
 * codage, pointeur vers l'espace mémoire qui va stocker le codage lu.
 * nomFichier, le nom du fichier qui contient le codage à lire.
 *
 * RETOUR
 * 0, la lecture s'est réalisé correctement.
 * -1, pointeur vers le codage vaut NULL.
 * -2, pointeur vers la suite de Prufer dans le codage vaut NULL.
 * -3, pointeur vers le nom du fichier non valide (= NULL).
 * -4, impossible d'ouvrir le fichier qui contient le codage.
 *
 * ------------------------------------------------------------------------- */
int lire_codage_prufer(CodagePrufer *codage, char *nomFichier);

/* ------------------------------------------------------------------------- *
 * Génére le codage de Prüfer pour un arbre donnée.
 * ATTENTION : cette fonction modifie le graphe de départ.
 *
 * PARAMETERS
 * arbre, l'arbre dont on veut obtenir le codage de Prüfer.
 *
 * RETOUR
 * Un pointeur vers CodagePrufer (structure) qui contient le codage de Prüfer
 * 	de l'arbre donné.
 * NULL en cas d'erreur.
 *
 * ------------------------------------------------------------------------- */
CodagePrufer* generer_codage_prufer(GRAPHE* arbre);

/* ------------------------------------------------------------------------- *
 * Génére le graphe associé au codage de Prüfer donné.
 *
 * PARAMETERS
 * codage, un pointeur vers le codage de Prüfer à décoder.
 *
 * RETOUR
 * 0, aucune erreur.
 * -1, pointeur vers le codage vaut NULL.
 * -2, pointeur vers l'arbre vaut NULL.
 * -3, pointeur vers le tableau des degrés vaut NULL.
 *
 * ------------------------------------------------------------------------- */
int decoder_codage_prufer(GRAPHE *arbre, CodagePrufer *codage);

#endif
