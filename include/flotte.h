// include/flotte.h
#ifndef FLOTTE_H
#define FLOTTE_H

typedef enum {
	LIBRE,
	OCCUPE
}StatutVehicule;

typedef struct {
	double charge;
	int emplacement;
	int autonomie;
	StatutVehicule statut;
}Vehicule;

typedef struct {
	int nbVehicules;
	int horizonTemporel;
	int autonomie;
	int dureeRecharge;
	Vehicule *vehicules;
}Flotte;

#include <stdio.h>
#include "matrice.h"

void lireFichierFlotte(Flotte *flotte, char const *nomFichier);
void initialiserPositionInitialeFlotte(Flotte *flotte, Matrice *dureeTrajet);
void afficherPositionInitialeFlotte(Flotte *flotte);
void imprimerPositionInitialeFlotte(Flotte *flotte, FILE *fichier);
void libererFlotte(Flotte *flotte);

#endif