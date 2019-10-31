#include <stdio.h>
#include <stdlib.h>

#include "prufer.h"

CodagePrufer *creer_codage_prufer(unsigned int taille){

	CodagePrufer *nvCodage = malloc(sizeof(CodagePrufer));
	if(nvCodage == NULL){
		fprintf(stderr, "** ERREUR : Erreur à l'allocation du codage de Prüfer.\n");
		return NULL;
	}

	nvCodage->taille = taille;
	nvCodage->suitePrufer = malloc(sizeof(int) * taille);
	if(nvCodage->suitePrufer == NULL){
		fprintf(stderr, "** ERREUR : Erreur à l'allocation de la suite de Prüfer.\n");
		free(nvCodage);
		return NULL;
	}

	for(size_t i = 0; i < taille; i++)
		nvCodage->suitePrufer[i] = 0;

	return nvCodage;
}//Fin creer_codage_prufer()

void detruire_codage_prufer(CodagePrufer *codage){
	if(codage == NULL)
		return;

	if(codage->suitePrufer != NULL)
		free(codage->suitePrufer);

	free(codage);
	return;
}//Fin detruire_codage_prufer()

void afficher_codage_prufer(CodagePrufer *codage){
	if(codage == NULL){
		fprintf(stderr, "Pointeur vers codage vaut NULL\n");
		return;
	}
	if(codage->suitePrufer == NULL){
		fprintf(stderr, "Pointeur vers la suite de Prüfer vaut NULL\n");
		return;
	}

	printf("Codage : ");

	for(unsigned int i = 0; i < codage->taille; i++){
		printf("%d ", codage->suitePrufer[i]);
	}
	printf("\n");
}//Fin afficher_codage_prufer()

int lire_taille_codage(char *nomFichier){
	if(nomFichier == NULL){
		fprintf(stderr, "Pointeur vers nomFichier vaut NULL\n");
		return -1;
	}

	FILE* fichierCodage = fopen(nomFichier, "r");
	if(fichierCodage == NULL){
		fprintf(stderr, "Impossible d'ouvrir le fichier.\n");
		return -2;
	}

	unsigned int taille;

	fscanf(fichierCodage, "%u", &taille);

	if(fichierCodage != NULL)
		fclose(fichierCodage);

	return ((int)taille);
}//Fin lire_taille_codage()

int lire_codage_prufer(CodagePrufer *codage, char *nomFichier){
	if(codage == NULL){
		fprintf(stderr, "Pointeur vers codage vaut NULL\n");
		return -1;
	}
	if(codage->suitePrufer == NULL){
		fprintf(stderr, "Pointeur vers la suite de Prüfer vaut NULL\n");
		return -2;
	}
	if(nomFichier == NULL){
		fprintf(stderr, "Pointeur vers nomFichier vaut NULL\n");
		return -3;
	}

	FILE* fichier = fopen(nomFichier, "r");
	if(fichier == NULL)
		return -4;

	int nombreLu;

	unsigned int tailleCodage;

	fscanf(fichier, "%u\n", &tailleCodage);

	for(unsigned int i = 0; i < tailleCodage; i++){
		fscanf(fichier, "%d ", &nombreLu);
		codage->suitePrufer[i] = nombreLu;
	}//Fin for()

	if(fichier != NULL)
		fclose(fichier);

	return 0;
}//Fin lire_codage_prufer()

CodagePrufer* generer_codage_prufer(GRAPHE* arbre){
	if(arbre == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers le graphe vaut NULL.\n");
		return NULL;
	}
	if(arbre->premierSommet == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers le premier sommet du graphe vaut NULL.\n");
		return NULL;
	}
	if(arbre->nbS <= 2){
		fprintf(stderr, "** ERREUR : votre arbre contient moins de 3 sommets donc on ne peut PAS en trouver le codage de Prüfer.\n");
		return NULL;
	}

	//Un codage de Prüfer contient tjrs #V - 2 éléments.
	CodagePrufer* nvCodage = creer_codage_prufer(arbre->nbS - 2);
	if(nvCodage == NULL){
		fprintf(stderr, "** ERREUR à la création de la structure du codage de Prüfer.\n");
		return NULL;
	}

	int indiceCodage = 0;
	SOMMET* tmpSommet;
	Tableau* voisinsSommet;
	int indiceSommetCourant;

	while(indiceCodage < arbre->nbS - 2){

		indiceSommetCourant = 1;

		//On doit trouver la feuille de plus petit indice donc un sommet de degré 1.
		while(indiceSommetCourant <= arbre->nbS){

			//On récupére les voisins du sommet de label indiceSommetCourant.
			//S'il a plus de 1 voisin alors ce n'est pas une feuille.

			voisinsSommet = obtenir_voisins_sommet(arbre, indiceSommetCourant);
			if(voisinsSommet != NULL){
				//S'il a bien un unique voisin.
				if(voisinsSommet->dernierElementUtilise == 1){
					//On vérifie si on n'a pas déjà considérer la feuille.
					tmpSommet = obtenir_sommet(arbre, indiceSommetCourant);
					if(tmpSommet != NULL){
						if(tmpSommet->info != 1){
							break;
						}
					}
				}//Fin if()
			}//Fin if()

			indiceSommetCourant++;

			if(voisinsSommet != NULL)
				free(voisinsSommet);
		}//Fin while()

		//On a trouvé un sommet de degré 1 (une feuille).
		//On récupére son unique voisin.

		ELTADJ* voisinFeuille = obtenir_voisin(arbre, indiceSommetCourant);
		if(voisinFeuille == NULL){
			fprintf(stderr, "** ERREUR : imossible de récupérer le voisin dans generer_codage_prufer.\n");
			detruire_codage_prufer(nvCodage);
			return NULL;
		}

		//On ajoute le label de son unique voisin à la suite de Prüfer.
		nvCodage->suitePrufer[indiceCodage] = voisinFeuille->dest;

		indiceCodage++;

		//On marque la feuille de plus petit label comme déjà considérée.
		tmpSommet = obtenir_sommet(arbre, indiceSommetCourant);
		if(tmpSommet != NULL){
			tmpSommet->info = 1;
		}

		//On supprime les arcs entre la feuille et son adjacent.
		supprimerArc(arbre, indiceSommetCourant, voisinFeuille->dest);
		supprimerArc(arbre, voisinFeuille->dest, indiceSommetCourant);

		afficher_codage_prufer(nvCodage);
	}//Fin while()

	return nvCodage;
}//Fin generer_codage_prufer()

int decoder_codage_prufer(GRAPHE *arbre, CodagePrufer *codage){
	if(codage == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers le codage vaut NULL.\n");
		return -1;
	}

	int nbSommetsG = codage->taille + 2;

	int *degres = malloc(sizeof(int) * nbSommetsG);
	if(degres == NULL)
		return -2;

	for(int i = 0; i < nbSommetsG; ++i){
		ajouterSommet(arbre, 0);
		degres[i] = 1;
	}

	//On calcule les degrés des sommets
	for(size_t i = 0; i < codage->taille; ++i){
		for(int j = 0; j < nbSommetsG; ++j){

			if(codage->suitePrufer[i] == j + 1)
				++degres[j];
		}
	}

	//On construit le graphe sur base du codage
	for(size_t i = 0; i < codage->taille; ++i){
		for(int j = 0; j < nbSommetsG - 2; ++j){

			if(degres[j] == 1){
				ajouterArc(arbre, j + 1, codage->suitePrufer[j], 0);
				ajouterArc(arbre, codage->suitePrufer[j], j + 1, 0);

				--degres[j];
				--degres[codage->suitePrufer[j] - 1];
			}
		}
	}

	//On rattache les deux derniers sommets de degrés 1
	int premierSommet = 0, deuxiemeSommet = 0;

	int i, j;

	for(i = 0; i < nbSommetsG; ++i){
		if(degres[i] == 1){
			premierSommet = i + 1;
			--degres[i];
			break;
		}
	}

	for(j = i; j < nbSommetsG; ++j){
		if(degres[j] == 1){
			deuxiemeSommet = j + 1;
			--degres[j];
			break;
		}
	}

	ajouterArc(arbre, premierSommet, deuxiemeSommet, 0);
	ajouterArc(arbre, deuxiemeSommet, premierSommet, 0);

	if(degres != NULL)
		free(degres);

	return 0;
}//Fin decoder_codage_prufer()
