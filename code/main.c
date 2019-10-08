#include <stdio.h>
#include <stdlib.h>

#include "graphes.h"

int main(/*int argc, char** argv*/void){

  printf("It's working.\n");

	//Exemple
	GRAPHE g;
	lireFichier("test.txt", &g);
	afficherGraphe(&g);
	supprimerGraphe(&g);

  return 0;
}
