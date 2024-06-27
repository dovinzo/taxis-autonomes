#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/matrice.h"

void creerMatrice(Matrice *matrice, int nombreLignes, int nombreColonnes)
{
	matrice->nombreLignes = nombreLignes;
	matrice->nombreColonnes = nombreColonnes;
	matrice->coefficients = (int*)malloc(nombreLignes*nombreColonnes*sizeof(int));
	if (NULL == matrice->coefficients)
	{
		printf("Erreur : echec lors d'une allocation dynamique de memoire\n");
		exit(EXIT_FAILURE);
	}
}

int getElementMatrice(Matrice *matrice, int i, int j)
{
	assert(1 <= i && i <= matrice->nombreLignes && 1 <= j && j <= matrice->nombreColonnes);
	return matrice->coefficients[(j-1)*matrice->nombreLignes+(i-1)];
}

void setElementMatrice(Matrice *matrice, int i, int j, int element)
{
	matrice->coefficients[(j-1)*matrice->nombreLignes+(i-1)] = element;
}

void libererMatrice(Matrice *matrice)
{
	free(matrice->coefficients);
	matrice->nombreLignes = 0;
	matrice->nombreColonnes = 0;
}

void matriceNulle(Matrice *matrice)
{
	for (int i = 1 ; i <= matrice->nombreLignes ; i++)
	{
		for (int j = 1 ; j <= matrice->nombreColonnes ; j++)
		{
			setElementMatrice(matrice, i, j, 0);
		}
	}
}

void afficherMatrice(Matrice *matrice)
{
	for (int i = 1 ; i <= matrice->nombreLignes ; i++)
	{
		printf("|");
		for (int j = 1 ; j <= matrice->nombreColonnes ; j++)
		{
			printf(" %3d", getElementMatrice(matrice, i, j));
		}
		printf(" |\n");
	}
}