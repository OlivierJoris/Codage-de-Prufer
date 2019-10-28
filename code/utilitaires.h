#ifndef __UTILITAIRES__
#define __UTILITAIRES__

#include <unistd.h>
#include <getopt.h>

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
 * -1, si erreur.
 * 1, si encodage
 * 2, si decodage
 *
 * ------------------------------------------------------------------------- */
ModeUtilisation gestion_des_arguments(int argc, char **argv, char *source);

#endif
