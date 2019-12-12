/* ------------------------------------------------------------------------- *
 * Fichier qui contient une énumération représentant les différents modes
 * d'utilisation du programme.
 * Ainsi que les prototypes de la fonction pour gérer les arguments du
 * programme et de la fonction pour générer un nombre aléatoire entre
 * 2 bornes.
 * ------------------------------------------------------------------------- */

#ifndef __UTILITAIRES__
#define __UTILITAIRES__

#include <unistd.h>
#include <getopt.h>

//Résultats possibles après l'analyse des arguments fournis au programme.
typedef enum {erreur = -1, encodage, decodage}ModeUtilisation;

/* ------------------------------------------------------------------------- *
 ** Fonction pour gérer les arguments au lancement du programme.
 *
 ** PARAMETRES
 * argc, le nombre d'arguments.
 * argv, le tableau de chaines de caractères contenant l'ensemble des arguments.
 * fichier, le fichier dans lequel il faut lire le graphe/codage de Prufer.
 *
 ** RETOUR
 * erreur, si erreur.
 * encodage, si encodage
 * decodage, si decodage
 *
 * ------------------------------------------------------------------------- */
ModeUtilisation gestion_des_arguments(int argc, char **argv, char *source);

/* ------------------------------------------------------------------------- *
** Fonction pour générer un nombre aléatoire dans [borneMin...borneMax].
*
** Paramètres :
* borneMin, la borne inférieure de l'intervalle de génération.
* borneMax, la borne supérieur de l'intervalle de génération.
*
** Retour :
* EXIT_FAILURE, borneMin > borneMax.
* Sinon, le nombre généré.
*
 * ------------------------------------------------------------------------- */
int generer_nombre_aleatoire(const int borneMin, const int borneMax);

#endif
