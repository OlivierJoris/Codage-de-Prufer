#ifndef __PRUFER__
#define  __PRUFER__

typedef struct CodagePrufer_t{
	unsigned int taille;
	char *suitePrufer;
}CodagePrufer;

CodagePrufer *creer_codage_prufer(unsigned int taille);

void detruire_codage_prufer(CodagePrufer *codage);

void afficher_codage_prufer(CodagePrufer *codage);

int lire_taille_codage(char *nomFichier);

int lire_codage_prufer(CodagePrufer *codage, char *nomFichier);

#endif
