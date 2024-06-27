// include/appels.h
#ifndef APPELS_H
#define APPELS_H

typedef struct {
	int heure;
	char nomClient[25];
	int origine;
	int destination;
	int heureMinimale;
	int heureMaximale;
	int prime;
}Appel;

typedef struct {
	int nbAppels;
	Appel *appels;
}Appels;

#include <stdio.h>

void lireFichierAppels(Appels *appels, char const *nomFichier);
void libererAppels(Appels *appels);

#endif