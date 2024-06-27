// include/matrice.h
#ifndef MATRICE_H
#define MATRICE_H

typedef struct {
	int nombreLignes;
	int nombreColonnes;
	int *coefficients;
}Matrice;

void creerMatrice(Matrice *matrice, int nombreLignes, int nombreColonnes);
int getElementMatrice(Matrice *matrice, int i, int j);
void setElementMatrice(Matrice *matrice, int i, int j, int element);
void libererMatrice(Matrice *matrice);
void matriceNulle(Matrice *matrice);
void afficherMatrice(Matrice *matrice);

#endif