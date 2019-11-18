/* ------------------------------------------------------------------------- *
 * Fichier qui contient les fonctions pour manipuler un graphe et obtenir
 * des informations sur le graphe.
 * ------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

#include "utilitaires.h"
#include "tableau.h"
#include "graphes.h"

void initialiserGraphe(GRAPHE *g){

	g->nbS = 0;
	g->nbA = 0;
	g->maxS = 0;
	g->premierSommet = NULL;
	g->dernierSommet = NULL;
}//Fin initialiserGraphe()

int ajouterSommet(GRAPHE *g, int info){

	SOMMET *pointeur;

	g->maxS++;
	pointeur = (SOMMET *) malloc(sizeof(SOMMET));
	if (pointeur == NULL){
		printf("Erreur! Memoire insuffisante pour creer un sommet\n");
		return -1;
	}else{
		pointeur->label = g->maxS;
		pointeur->info = info;
		pointeur->suivant = NULL;
		pointeur->adj = NULL;
		if(g->nbS == 0){
			g->premierSommet = pointeur;
			g->dernierSommet = pointeur;
		}else{
			g->dernierSommet->suivant = pointeur;
			g->dernierSommet = pointeur;
		}
		g->nbS++;
		return pointeur->label;
	}
}//Fin ajouterSommet()

int ajouterArc(GRAPHE *g, int a, int b, int info){

	SOMMET *psommet, *psommet2;
	ELTADJ *padj, *precedent;

	psommet = g->premierSommet;

	/* on parcourt les sommets jusqu'a trouver a */
	while(psommet != NULL){
		if(psommet->label == a) break;
		psommet = psommet->suivant;
	}

	if(psommet == NULL){
		printf("Erreur! Creation d'un arc dont l'origine n'existe pas\n");
		return -1;
	}else /* on a trouver a */
	{
		padj = psommet->adj;

		/* on parcourt les sommets pour trouver b */
		psommet2 = g->premierSommet;
		while(psommet2 != NULL){
			if(psommet2->label == b) break;
			psommet2 = psommet2->suivant;
		}
		if(psommet2 == NULL){
			printf("Erreur! Creation d'un arc dont l'extremite n'existe pas\n");
			return -2;
		}else /* on a trouver a et b */
		{
			if (padj == NULL) /* la liste d'adjacence est vide */
			{
				padj = (ELTADJ *) malloc(sizeof(ELTADJ));
				if(padj == NULL){
					printf("Erreur! Memoire insuffisante pour creer un sommet\n");
					return -3;
				}else{
					psommet->adj = padj; /* premier element de la liste d'adjacence */
					padj->suivant = NULL;
				}
			}else /* la liste d'adjacence est non vide, on la parcourt pour voir si b s'y trouve */
			{
				if (padj->dest > b){
					padj = (ELTADJ *) malloc(sizeof(ELTADJ));
					if(padj == NULL){
						printf("Erreur! Memoire insuffisante pour creer un sommet\n");
						return -3;
					}else{
						padj->suivant=psommet->adj;
						psommet->adj=padj;
					}
				}else{
					while(padj != NULL){
						if (padj->dest == b) {padj->info = info; break;} /* l'arc existe, update info */
						if (padj->dest > b) {padj = NULL; break;} /* on depasse b sans le trouver */
						precedent=padj;
						padj=padj->suivant;
					}

					if (padj == NULL) /* l'arc n'existe pas, il faut le creer */
					{
						padj = (ELTADJ *) malloc(sizeof(ELTADJ));
						if(padj == NULL){
							printf("Erreur! Memoire insuffisante pour creer un sommet\n");
							return -3;
						}else
							if (precedent->suivant == NULL) /* element ajouter a la fin */
							{
								precedent->suivant = padj;
								padj->suivant = NULL;
							}else /* element ajouter "au milieu" pour garder ordre */
							{
								padj->suivant = precedent->suivant;
								precedent->suivant = padj;
							}
					}
				}
			}
			padj->dest = b;
			padj->info = info;
			g->nbA++;
		}
		return 0;
	}
}//Fin ajouterArc()


int supprimerSommet(GRAPHE *g, int label){

	SOMMET *psommet, *precedent;
	ELTADJ *padj, *suivant, *precedent_adj;
	int flag_premier_sommet, flag_premier_arc;

	if(g->premierSommet == NULL){
		printf("Erreur! Graphe vide, suppression impossible\n");
		return -1;
	}else{
		psommet = g->premierSommet;
		flag_premier_sommet = 1;
		while(psommet != NULL){
			if(psommet->label == label) break;
			else{
				flag_premier_sommet = 0;
				precedent = psommet;
				psommet = psommet->suivant;
			}
		}
		if(psommet == NULL){
			printf("Erreur! Le sommet a supprimer n'existe pas\n");
			return -1;
		}else{
			if(psommet->suivant == NULL) g->dernierSommet = precedent;

			if(flag_premier_sommet == 1) g->premierSommet = psommet->suivant;
			else precedent->suivant = psommet->suivant;
			padj = psommet->adj;
			free(psommet);
			g->nbS--;
			while(padj != NULL){
				suivant = padj->suivant;
				free(padj);
				g->nbA--;
				padj = suivant;
			}
		}

		/* il faut aussi supprimer les arcs ayant le sommet a supprimer comme extremite */
		psommet = g->premierSommet;
		while(psommet != NULL){
			padj = psommet->adj;
			flag_premier_arc = 1;

			while(padj != NULL) {
				if(padj->dest == label) break;
				else{
				flag_premier_arc = 0;
				precedent_adj = padj;
				padj = padj->suivant;
				}
			}
			if(padj != NULL){
				if(flag_premier_arc == 1) psommet->adj = padj->suivant;
				else precedent_adj->suivant = padj->suivant;
				free(padj);
				g->nbA--;
			}
			psommet=psommet->suivant;
		}
		return 0;
	}
}//Fin supprimerSommet()

int supprimerArc(GRAPHE *g, int a, int b){

	SOMMET *psommet;
	ELTADJ *padj, *precedent_adj;
	int flag_premier_arc;

	if(g->premierSommet == NULL){
		printf("Erreur! Graphe vide, suppression impossible\n");
		return -1;
	}else{
		psommet = g->premierSommet;
		while(psommet != NULL){
			if(psommet->label == a) break;
			else psommet = psommet->suivant;
		}

		if(psommet == NULL){
			printf("Erreur! L'extremite de l'arc a supprimer n'existe pas\n");
			return -1;
		}else{
			padj = psommet->adj;
			flag_premier_arc = 1;
			while(padj != NULL){
				if(padj->dest == b) break;
				else{
					flag_premier_arc = 0;
					precedent_adj = padj;
					padj = padj->suivant;
				}
			}

			if(padj != NULL){
				if(flag_premier_arc == 1) psommet->adj = padj->suivant;
				else precedent_adj->suivant = padj->suivant;
				free(padj);
				g->nbA--;
			}else{
				printf("Erreur! L'extremite de l'arc a supprimer n'existe pas\n");
				return -1;
			}
		}
		return 0;
	}
}//Fin supprimerArc()

void supprimerGraphe(GRAPHE *g){

	SOMMET *psommet,*temps;
	ELTADJ *padj,*tempadj;

	psommet = g->premierSommet;

	while(psommet != NULL){
		padj = psommet->adj;
		while(padj !=NULL){
			tempadj = padj;
			padj = padj->suivant;
			free(tempadj);
		}

		temps = psommet;
		psommet = psommet->suivant;
		free(temps);
	}
	initialiserGraphe(g);
}//Fin supprimerGraphe()

void afficherGraphe(GRAPHE *g){

	SOMMET *psommet;
	ELTADJ *padj;

	if(g->premierSommet == NULL) printf("graphe vide\n");
	else{
		printf("nbS=%d , nbA=%d, label max.=%d\n", g->nbS, g->nbA, g->maxS);
		psommet = g->premierSommet;

		do{
			printf("\n");
			printf("Sommet de label: %d , info: %d\n", psommet->label, psommet->info);
			if(psommet->adj == NULL) printf(" -> ce sommet n'a aucun arc sortant\n ");
			else{
				padj = psommet->adj;

				do{
					printf(" -> arc de %d vers %d avec l'info. %d \n", psommet->label, padj->dest, padj->info);
					padj = padj->suivant;
				}while(padj != NULL);
			}
			printf("\n");
			psommet = psommet->suivant;
		}while(psommet != NULL);
	}
}//Fin afficherGraphe()

int lireFichier(char *nomf, GRAPHE *g){

  FILE *fp;
  char ligne[MAX+1];
  int temp, i, j,nbS1 , nbLigne, sommet, nbElt, creerArc;

	initialiserGraphe(g);
  fp = fopen(nomf, "r"); /* ouvre un fichier en lecture */
	if(fp == NULL){
		fprintf(stderr, "** ERREUR ouverture fichier.\n");
		return -1;
	}
  nbLigne = 0; /* compte les lignes du fichier */
  sommet = 0; /* label du sommet en cours */
  nbS1 = 0; /* compte les sommets de la 1ere ligne */
  while(fgets(ligne, MAX, fp) != NULL){
    nbLigne++; /* compte le nombre de lignes du fichier */

    if(ligne[0] != '\n') /* on passe les lignes vides */
		{
			i = 0;
			if(nbS1 == 0) /* compte les sommets de la 1ere ligne */
			{
				nbS1 = 1;
				while(ligne[i] != '\n'){
					if(ligne[i] == ',')
						nbS1++;
					i++;
				}
				for(j = 1; j <= nbS1; j++){
					ajouterSommet(g, 0);
				}
				i = 0; /* on relit la 1ere ligne */
			}

			sommet++; /* origine des arcs */
			nbElt = 0; /* controle le nombre d'arcs crees */
			while(ligne[i] != '\n'){
				temp = 0; /* va contenir l'extremite */
				creerArc = 1;
				while(ligne[i] != ',' && ligne[i] != '\n'){
					while (ligne[i] == ' ' || ligne[i] == '\t'){
						i++;
					}

					if((ligne[i] > '9' || ligne[i] < '0') && ligne[i] != 'x'){
						printf("Erreur à la ligne %d !\n", nbLigne);
						supprimerGraphe(g);
						return -1; /* pas des chiffres ! */
					}

					if(ligne[i]=='x')
						creerArc=0;

					temp = 10 * temp + ligne[i] - '0';
					i++;
					while(ligne[i] == ' ' || ligne[i] == '\t'){
						i++;
					}
				}
				if(ligne[i] == ',')
					i++;

				nbElt++;

				if(nbElt <= nbS1 && creerArc==1)
					ajouterArc(g, sommet, nbElt, temp); /* ligne pas trop longue */
			}
			if(nbElt != nbS1) /* pas le bon nombre de champs sur ligne */
			{
				printf("Erreur à la ligne %d !\n", nbLigne);
				supprimerGraphe(g);
				return -1; /* pas le bon nombre de champs */
			}
		}
  }
  fclose(fp);
	return 0;
}//Fin lireFichier()

//Sauvegarder le graphe dans un fichier revient à constituer la matrice d'adjacence du graphe dans un fichier.
//Le graphe sera toujours sauvegradé dans le fichier output_graph.txt. Si ce fichier n'existe pas, il sera créé automatiquement.
//A condition que l'utilisateur possède le droit d'écriture dans le dossier dans lequel le programme est lancé.
int sauvegarder_graphe(GRAPHE *g){
	if(g == NULL)
		return -1;

	if(g->premierSommet == NULL)
		return -2;

	//Pointeur temporaire car manipulations de listes chainées.
	SOMMET *sommetCourant = g->premierSommet;
	ELTADJ *sommetAdj = g->premierSommet->adj;

	FILE* fichierGraphe = fopen("output_graph.txt", "w");
	if(fichierGraphe == NULL)
		return -3;

	//Initialisation copie.

	//Si le premier sommet du graphe n'est pas d'indice 1, on remplit de #V 'x' les premières lignes.
	if(sommetCourant->label > 1){
		//Remplir les lignes.
		for(int i = 1; i < sommetCourant->label; i++){
			//Remplir une ligne.
			for(int j = 1; j < g->nbS; j++){
				fprintf(fichierGraphe, "x,");
			}//Fin for()
			//Cas séparé car on ne veut pas de virgule en fin de ligne.
			fprintf(fichierGraphe, "x");
			fprintf(fichierGraphe, "\n");
		}//Fin for()
	}//Fin if()

	int posLigneFichier = 1;

	//Parcourir l'entierté des sommets.
	while(sommetCourant != NULL){
		sommetAdj = sommetCourant->adj;
		//Parcurir les sommets adjacents à un sommet. (liste adjacence pour un sommet.)
		while(sommetAdj != NULL){
			//On remplit de 'x' jusqu'à (non compris) un sommet pour lequel il existe un arc entre ce sommet et sommetCourant.
			if(sommetAdj->dest > posLigneFichier){
				for(int j = posLigneFichier; j < sommetAdj->dest; j++){
					fprintf(fichierGraphe, "x,");
				}//Fin for()
			}//Fin if()

			posLigneFichier = sommetAdj->dest + 1;

			fprintf(fichierGraphe, "%d", sommetAdj->info);
			//Si on est pas au dernier sommet, on met une vrigule.
			if(posLigneFichier <= g->nbS)
				fprintf(fichierGraphe, ",");

			//On passe au sommet suivant de la liste d'adjacence de sommetCourant.
			sommetAdj = sommetAdj->suivant;
		}//Fin while()
		//S'il n'existe pas d'arc entre le sommetCourant et le dernier sommet (en terme d'indice) du graphe, on remplit de 'x' jusqu'au dernier sommet du graphe.
		if(posLigneFichier <= g->nbS){
			for(int i = posLigneFichier; i < g->nbS; i++)
				fprintf(fichierGraphe, "x,");
			//On ne doit pas mettre de virgule en fin de ligne donc on le fait en dehors de la boucle.
			fprintf(fichierGraphe, "x");
		}
		//On change de sommet donc on passe à la ligne suivante de la matrice d'adjacence.
		fprintf(fichierGraphe, "\n");
		posLigneFichier = 1;
		//On passe au sommet suivant du graphe.
		sommetCourant = sommetCourant->suivant;
	}//Fin while()

	if(fichierGraphe != NULL)
		fclose(fichierGraphe);

	printf("Le graphe a été sauvegardé dans le fichier 'output_graph.txt'.\n");

	return 0;
}//Fin sauvegarder_graphe()

SOMMET* obtenir_sommet(GRAPHE* g, int labelSommet){
	if(g == NULL)
		return NULL;

	if(g->premierSommet == NULL)
		return NULL;

	if(labelSommet < 1){
		fprintf(stderr, "** ERREUR : vous essayez de récupérer un sommet dont le label < 1.\n");
		return NULL;
	}

	if(labelSommet > g->nbS){
		fprintf(stderr, "** ERREUR : vous essayer d'obtenir le sommet %d mais le graphe ne contient que %d sommets.\n", labelSommet, g->nbS);
		return NULL;
	}

	//1 car on sait qu'on a au moins 1 sommet sinon g->premierSommet vaudrait NULL.
	int labelSommetCourant = 1;
	SOMMET* tmpSommet = g->premierSommet;

	//On parcourt la liste jusqu'à arriver au sommet avec le label labelSommet.
	while(labelSommetCourant < labelSommet){
		if(tmpSommet->suivant == NULL){
			fprintf(stderr, "** ERREUR dans le parcours de la liste.\n");
			return NULL;
		}
		tmpSommet = tmpSommet->suivant;
		labelSommetCourant++;
	}//Fin while()

	//Le sommet n'existe pas.
	if(tmpSommet->label != labelSommet){
		fprintf(stderr, "** ERREUR : Le sommet demandé est le sommet %d est on est au sommet %d\n", labelSommet, tmpSommet->label);
		return NULL;
	}

	return tmpSommet;
}//Fin obtenir_sommet()

ELTADJ* obtenir_voisin(GRAPHE* g, int labelSommet){
	if(g == NULL)
		return NULL;

	if(g->premierSommet == NULL)
		return NULL;

	if(labelSommet < 1){
		fprintf(stderr, "** ERREUR : vous essayez de récupérer le voisin d'un sommet dont le label < 1.\n");
		return NULL;
	}

	if(labelSommet > g->nbS){
		fprintf(stderr, "** ERREUR : vous essayer d'obtenir le voisin du sommet %d mais le graphe ne contient que %d sommets.\n", labelSommet, g->nbS);
		return NULL;
	}

	SOMMET* tmpSommet = g->premierSommet;
	//1 car on sait qu'on a au moins 1 sommet sinon g->premierSommet vaudrait NULL.
	int labelSommetCourant = 1;

	//On parcourt la liste jusqu'à arriver au sommet avec le label labelSommet.
	while(labelSommetCourant < labelSommet){
		if(tmpSommet->suivant == NULL){
			fprintf(stderr, "** ERREUR dans le parcours de la liste.\n");
			return NULL;
		}
		tmpSommet = tmpSommet->suivant;
		labelSommetCourant++;
	}//Fin while()

	//Le sommet n'existe pas.
	if(tmpSommet->label != labelSommet){
		fprintf(stderr, "** ERREUR : Le sommet demandé est le sommet %d est on est au sommet %d\n", labelSommet, tmpSommet->label);
		return NULL;
	}

	return tmpSommet->adj;
}//Fin obtenir_voisin()

Tableau* obtenir_voisins_sommet(GRAPHE* g, int labelSommet){
	if(g == NULL)
		return NULL;

	if(g->premierSommet == NULL)
		return NULL;

	if(labelSommet < 1){
		fprintf(stderr, "** ERREUR : vous essayez de récupérer un sommet dont le label < 1.\n");
		return NULL;
	}

	if(labelSommet > g->nbS){
		fprintf(stderr, "** ERREUR : vous essayer d'obtenir les voisins du sommet %d mais le graphe ne contient que %d sommets.\n", labelSommet, g->nbS);
		return NULL;
	}

	SOMMET* tmpSommet = g->premierSommet;
	//1 car on sait qu'on a au moins 1 sommet sinon g->premierSommet vaudrait NULL.
	int labelSommetCourant = 1;

	//On parcourt la liste jusqu'à arriver au sommet avec le label labelSommet.
	while(labelSommetCourant < labelSommet){
		if(tmpSommet->suivant == NULL){
			fprintf(stderr, "** ERREUR dans le parcours de la liste.\n");
			return NULL;
		}
		tmpSommet = tmpSommet->suivant;
		labelSommetCourant++;
	}//Fin while()

	//Le sommet n'existe pas.
	if(tmpSommet->label > labelSommet)
		return NULL;


	//La liste des sommets adjacents au sommet considéré (labelSommet) est ses voisins.
	ELTADJ* listeSommetsAdjacents = tmpSommet->adj;
	Tableau* voisins = creer_tableau();
	if(voisins == NULL)
		return NULL;

	//Il faut parcourir la liste d'adjacence et récupérer 'dest' pour chaque sommet et mettre 'dest' dans un tableau.
	//Ainsi, le tableau contiendra les voisins du sommet labelSommet.
	while(listeSommetsAdjacents != NULL){
		ajouter_element_tab(voisins, listeSommetsAdjacents->dest);
		listeSommetsAdjacents = listeSommetsAdjacents->suivant;
	}//Fin while()

	return voisins;
}//Fin obtenir_voisins_sommet()

Tableau* obtenir_sommet_graphe(GRAPHE* g){
	if(g == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers le graphe vaut NULL.\n");
		return NULL;
	}
	if(g->premierSommet == NULL){
		fprintf(stderr, "** ERREUR : pointeur vers premierSommet vaut NULL.\n");
		return NULL;
	}

	Tableau* tabSommets = creer_tableau();
	if(tabSommets == NULL){
		fprintf(stderr, "** ERREUR à la création du tableau qui va contenir les sommets du graphe.\n");
		return NULL;
	}

	int resultatAJout;
	SOMMET* listeSommets = g->premierSommet;

	//Il faut parcourir la liste des sommets du graphe et ajouter le label de chaque sommet dans le tableau.
	while(listeSommets != NULL){

		resultatAJout = ajouter_element_tab(tabSommets, listeSommets->label);
		if(resultatAJout < 0){
			fprintf(stderr, "** ERREUR à l'ajout d'un élément dans le tableau dans obtenir_sommet_graphe.\n");
			detruire_tableau(tabSommets);
			return NULL;
		}//Fin if()

		if(listeSommets->suivant == NULL)
			break;
		else
			listeSommets = listeSommets->suivant;
	}//Fin while()

	return tabSommets;
}//Fin obtenir_sommet_graphe()

//Implémentation de l'algo. slide 130 beamer 1.
bool test_connexite(GRAPHE* g){
	if(g == NULL){
		fprintf(stderr, "** ERREUR le pointeur vers le graphe vaut NULL dans test_connexite.\n");
		return false;
	}

	int sommetAleatoire = generer_nombre_aleatoire(1, g->nbS);;

	Tableau* composante = creer_tableau();
	if(composante == NULL){
		fprintf(stderr, "** ERREUR à la création du tableau qui va contenir les composantes.\n");
		return false;
	}

	Tableau* new = creer_tableau();
	if(new == NULL){
		fprintf(stderr, "** ERREUR à la création du tableau new.\n");
		detruire_tableau(composante);
		return false;
	}

	//Initialisation

	int resultatAjout;

	resultatAjout = ajouter_element_tab(composante, sommetAleatoire);
	if(resultatAjout < 0){
		fprintf(stderr, "** ERREUR à l'ajout d'un élément dans le tableau composante.\n");
		detruire_tableau(composante);
		detruire_tableau(new);
		return false;
	}

	resultatAjout = ajouter_element_tab(new, sommetAleatoire);
	if(resultatAjout < 0){
		fprintf(stderr, "** ERREUR à l'ajout d'un élément dans le tableau new.\n");
		detruire_tableau(composante);
		detruire_tableau(new);
		return false;
	}

	Tableau* voisins = NULL;
	Tableau* voisinsSommet = NULL;
	Tableau* tmpRetourUnion = NULL;

	int resultatCopie;

	//Boucle principale

	while(new->nbreElements != 0){

		voisins = creer_tableau();
		if(voisins == NULL){
			fprintf(stderr, "** ERREUR à la création du tableau qui va contenir les voisins.\n");
			detruire_tableau(composante);
			detruire_tableau(new);
			return false;
		}

		for(size_t i = 0; i < new->nbreElements; i++){

			voisinsSommet = obtenir_voisins_sommet(g, new->donnees[i]);
			if(voisinsSommet == NULL){
				fprintf(stderr, "** ERREUR à la récupération des voisins.\n");
				detruire_tableau(composante);
				detruire_tableau(new);
				detruire_tableau(voisins);
				return false;
			}//Fin if()

			//fprintf(stderr, "Taille de voisins : %u || taille de voisinsSommet = %u.\n", voisins->nbreElements, voisinsSommet->nbreElements);
			tmpRetourUnion = union_tab(voisins, voisinsSommet);

			if(tmpRetourUnion == NULL){
				fprintf(stderr, "** ERREUR union voisins et voisinsSommet\n");
				detruire_tableau(composante);
				detruire_tableau(new);
				detruire_tableau(voisins);
				detruire_tableau(voisinsSommet);
				return false;
			}else{
				resultatCopie = copier_tableau(tmpRetourUnion, voisins);
				if(resultatCopie < 0){
					fprintf(stderr, "** ERREUR lors de la copie de tableau dans test_connexite.\n");
					detruire_tableau(composante);
					detruire_tableau(new);
					detruire_tableau(voisins);
					detruire_tableau(voisinsSommet);
					return false;
				}

				if(tmpRetourUnion != NULL){
					detruire_tableau(tmpRetourUnion);
					tmpRetourUnion = NULL;
				}
			}

			if(voisinsSommet != NULL){
				detruire_tableau(voisinsSommet);
				voisinsSommet = NULL;
			}
		}//Fin for()

		int resultatDiff = difference_tableaux(voisins, composante);
		if(resultatDiff < 0){
			fprintf(stderr, "** ERREUR lors de la différence de tableaux.\n");
			detruire_tableau(composante);
			detruire_tableau(new);
			detruire_tableau(voisins);
			detruire_tableau(voisinsSommet);
			return false;
		}

		resultatCopie = copier_tableau(voisins, new);
		if(resultatCopie < 0){
			fprintf(stderr, "** ERREUR lors de la copie de tableau dans test_connexite.\n");
			detruire_tableau(composante);
			detruire_tableau(new);
			detruire_tableau(voisins);
			detruire_tableau(voisinsSommet);
			return false;
		}

		tmpRetourUnion = union_tab(composante, new);
		if(tmpRetourUnion == NULL){
			fprintf(stderr, "** ERREUR lors de l'union de tableaux.\n");
			detruire_tableau(composante);
			detruire_tableau(new);
			detruire_tableau(voisins);
			detruire_tableau(voisinsSommet);
			return false;
		}else{
			resultatCopie = copier_tableau(tmpRetourUnion, composante);
			if(resultatCopie < 0){
				fprintf(stderr, "** ERREUR lors de la copie de tableau dans copier_tableau.\n");
				return false;
			}

			if(tmpRetourUnion != NULL){
				detruire_tableau(tmpRetourUnion);
				tmpRetourUnion = NULL;
			}
		}
		if(voisins != NULL){
			detruire_tableau(voisins);
			voisins = NULL;
		}
	}//Fin while()

	Tableau* sommetsGraphe = obtenir_sommet_graphe(g);
	if(sommetsGraphe == NULL){
		fprintf(stderr, "** ERREUR lors de la récupération des sommets du graphe.\n");
		detruire_tableau(composante);
		detruire_tableau(new);
		return false;
	}

	bool egaliteTab = egalite_tableaux(composante, sommetsGraphe);

	if(composante != NULL)
		detruire_tableau(composante);
	if(new != NULL)
		detruire_tableau(new);
	if(sommetsGraphe != NULL)
		detruire_tableau(sommetsGraphe);
	if(voisins != NULL)
		detruire_tableau(voisins);

	return egaliteTab;
}//Fin test_connexite()

bool contient_cycle(GRAPHE *g){
	if(g == NULL){
		fprintf(stderr, "** ERREUR le pointeur vers le graphe vaut NULL dans contient_cycle.\n");
		return true;
	}

	unsigned int degreSommet = 0;
	int retourSupprimerSommet = 0;

	if(g->premierSommet == NULL)
		return false;

	SOMMET *pSommet = g->premierSommet;
	ELTADJ *pAdj;

	//On calcule le degré de chaque sommet et on supprime ce sommet s'il est de degré 1
	while(pSommet != NULL){

		pAdj = pSommet->adj;

		// Ceci suffit car le graphe est non-orienté (vu la vérification de la fonction "est_non_oriente")
		while(pAdj != NULL){
			++degreSommet;
			pAdj = pAdj->suivant;
		}

		if(degreSommet == 1){

			retourSupprimerSommet = supprimerSommet(g, pSommet->label);
			if(retourSupprimerSommet < 0){
				fprintf(stderr, "** ERREUR lors de la suppression d'un sommet de l'arbre.\n");
				return true;
			}
			//On recommence à partir du premier sommet après avoir supprimer un sommet de degré 1 
			pSommet = g->premierSommet;
		}

		pSommet = pSommet->suivant;
		degreSommet = 0;
	}

	if(g->premierSommet->suivant == NULL)
		return false;

	return true;
}

bool est_non_oriente(GRAPHE *g){
	if(g == NULL){
		fprintf(stderr, "** ERREUR le pointeur vers le graphe vaut NULL dans est_non_oriente.\n");
		return false;
	}
	
	GRAPHE *tmp = g;
	SOMMET *pSommet = g->premierSommet, *pTmpSommet;
	ELTADJ *pAdj, *pTmpAdj;
	int labelSommetAdj = 0;
	bool arcEstPresent = false;

	// On parcourt le graphe
	while(pSommet != NULL){

		pAdj = pSommet->adj;

		// On parcourt les sommets adjacents au sommet actuel
		while(pAdj != NULL){

			pTmpSommet = g->premierSommet;
			labelSommetAdj = pSommet->adj->dest;

			// On se place sur le sommet de label labelSommetAdj
			while(pTmpSommet != NULL){

				if(pTmpSommet->label == labelSommetAdj)
					break;

				pTmpSommet = pTmpSommet->suivant;
			}

			pTmpAdj = pTmpSommet->adj;

			// On vérifie que l'arc est également présent dans l'autre sens
			while(pTmpAdj != NULL){
				
				if(pTmpAdj->dest == pSommet->label){
					arcEstPresent = true;
					break;
				}

				pTmpAdj = pTmpAdj->suivant;
			}

			// S'il n'est pas présent, le graphe n'est pas non-orienté
			if(!arcEstPresent)
				return false;

			// Sinon on continue avec les autres sommets adjacents
			pAdj = pAdj->suivant;
		}

		pSommet = pSommet->suivant;
	}

	g = tmp;
	
	return true;
}
