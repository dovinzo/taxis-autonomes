// include/voyages.h
#ifndef VOYAGES_H
#define VOYAGES_H

#include "liste_02.h"
#include "matrice.h"
#include "graphe.h"
#include "appels.h"

typedef struct {
	int heure;
	char nomClient[25];
	int duree;
	Liste_02 itineraire;
}Voyage;

typedef struct {
	int nbVoyages;
	Voyage *voyages;
}Voyages;

#include "appels.h"

void lireVoyages(Voyages *voyages, Appels *appels);
void lireDureeTrajetVoyages(Voyages *voyages, Matrice *dureeTrajet, Graphe *reseauRoutier, Appels *appels);
void triFusionVoyages(Voyage *voyages, int debut, int fin);
void fusionnerVoyages(Voyage *voyages, int debut, int milieu, int fin);
void afficherVoyages(Voyages *voyages);
void imprimerVoyages(Voyages *voyages, FILE *fichier);
void libererVoyages(Voyages *voyages);

#endif