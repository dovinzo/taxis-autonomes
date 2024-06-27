#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../include/graphe.h"
#include "../include/matrice.h"

void lireFichierGraphe(Graphe *graphe, char const *nomFichier)
{
	Matrice E;
	int i, j, k, compteur, aux;
	FILE *fichier = fopen(nomFichier,"r");
	if (NULL == fichier)
	{
		printf("Erreur : echec lors d'une ouverture de fichier\n");
		exit(EXIT_FAILURE);
	}
	fscanf(fichier, "%d %d\n", &(graphe->nombreSommets), &(graphe->nombreAretes));
	graphe->nombreAretes *= 2;
	graphe->V = (int*)malloc((graphe->nombreSommets+1)*sizeof(int));
	graphe->E = (int*)malloc(graphe->nombreAretes*sizeof(int));
	graphe->Lij = (int*)malloc(graphe->nombreAretes*sizeof(int));
	if (NULL == graphe->V || NULL == graphe->E || NULL == graphe->Lij)
	{
		printf("Erreur : echec lors d'une allocation dynamique de memoire\n");
		exit(EXIT_FAILURE);
	}
	creerMatrice(&E, graphe->nombreSommets, graphe->nombreSommets);
	matriceNulle(&E);
	for (k = 0 ; k < graphe->nombreAretes/2 ; k++)
	{
		fscanf(fichier, "%d %d %d\n", &i, &j, &aux);
		setElementMatrice(&E, i, j, aux);
		setElementMatrice(&E, j, i, aux);
	}

	k = 0;
	compteur = 0;
	for (i = 0 ; i < graphe->nombreSommets ; i++)
	{
		graphe->V[i] = compteur;
		for (j = 0 ; j < graphe->nombreSommets ; j++)
		{
			if (getElementMatrice(&E, i+1, j+1) > 0)
			{
				graphe->E[k] = j;
				graphe->Lij[k] = getElementMatrice(&E, i+1, j+1);
				k++;
				compteur++;
			}
		}
		graphe->V[graphe->nombreSommets] = compteur;
	}

	libererMatrice(&E);
	fclose(fichier);
}

void dijkstra(Graphe *graphe, int sdeb, Matrice *distance, Matrice *predecesseur)
{
	int s1;
	int *visited = (int*)malloc(graphe->nombreSommets*sizeof(int));
	if (NULL == visited)
	{
		printf("Erreur : echec lors d'une allocation dynamique de memoire\n");
		exit(EXIT_FAILURE);
	}
	initialisationDijkstra(sdeb, distance, visited, predecesseur);
	while (somme(visited, graphe->nombreSommets) < graphe->nombreSommets)
	{
		s1 = trouverMin(sdeb, distance, visited);
		visited[s1] = 1;
		for (int k = graphe->V[s1] ; k < graphe->V[s1+1] ; k++)
		{
			mettreAJourDistances(sdeb, s1, graphe->E[k], graphe->Lij[k], distance, visited, predecesseur);
		}
	}
	free(visited);
}

void initialisationDijkstra(int sdeb, Matrice *distance, int *visited, Matrice *predecesseur)
{
	for (int j = 0; j < distance->nombreColonnes ; j++)
	{
		setElementMatrice(distance, sdeb+1, j+1, INT_MAX);
		visited[j] = 0;
		setElementMatrice(predecesseur, sdeb+1, j+1, -1);
	}
	setElementMatrice(distance, sdeb+1, sdeb+1, 0);
}

int somme(int *tableau, int n)
{
	int somme = 0;

	for (int i = 0 ; i < n ; i++)
	{
		somme += tableau[i];
	}

	return somme;
}

int trouverMin(int sdeb, Matrice *distance, int *visited)
{
	int min = INT_MAX;
	int sommet = -1;
	for (int j = 0 ; j < distance->nombreColonnes ; j++)
	{
		if (!visited[j] && getElementMatrice(distance, sdeb+1, j+1) < min)
		{
			min = getElementMatrice(distance, sdeb+1, j+1);
			sommet = j;
		}
	}
	return sommet;
}

void mettreAJourDistances(int sdeb, int s1, int s2, int poids, Matrice *distance, int *visited, Matrice *predecesseur)
{
	if (!visited[s2] && getElementMatrice(distance, sdeb+1, s2+1) > getElementMatrice(distance, sdeb+1, s1+1)+poids)
	{
		setElementMatrice(distance, sdeb+1, s2+1, getElementMatrice(distance, sdeb+1, s1+1)+poids);
		setElementMatrice(predecesseur, sdeb+1, s2+1, s1);
	}
} 

void libererGraphe(Graphe *graphe)
{
	free(graphe->V);
	free(graphe->E);
	free(graphe->Lij);
	graphe->nombreSommets = 0;
	graphe->nombreAretes = 0;
}