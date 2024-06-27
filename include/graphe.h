// include/graphe.h
#ifndef GRAPHE_H
#define GRAPHE_H

typedef struct {
	int nombreSommets;
	int nombreAretes;
	int *V;
	int *E;
	int *Lij;
}Graphe;

#include "matrice.h"
#include "voyages.h"

void lireFichierGraphe(Graphe *graphe, char const *nomFichier);
void dijkstra(Graphe *graphe, int sdeb, Matrice *distance, Matrice *predecesseur);
void initialisationDijkstra(int sdeb, Matrice *distance, int *visited, Matrice *predecesseur);
int somme(int *tableau, int n);
int trouverMin(int sdeb, Matrice *distance, int *visited);
void mettreAJourDistances(int sdeb, int s1, int s2, int poids, Matrice *distance, int *visited, Matrice *predecesseur);
void libererGraphe(Graphe *graphe);

#endif