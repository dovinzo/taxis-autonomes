// include/gestionnaire_evenements.h
#ifndef GESTIONNAIRE_EVENEMENTS_H
#define GESTIONNAIRE_EVENEMENTS_H

#include "appels.h"
#include "liste_01.h"
#include "flotte.h"
#include "matrice.h"
#include "voyages.h"
#include "clients.h"
#include "file_attente.h"

void initialiserEvenements(Liste_01 *evenements, Appels *appels);
void traiterEvenement(Liste_01 *evenements, Appels *appels, Flotte *flotte, Matrice *dureeTrajet, FileAttente *fileAttente, int *nombreAppelsRefuses, int *nombreRechargesEffectuees, int *tempsTotalDeplacementVehicules, int *beneficeTotal);
void traiterEvenementAppel(Liste_01 *evenements, Flotte *flotte, Appels *appels, Matrice *dureeTrajet, int *nombreAppelsRefuses, int *beneficeTotal);
void declancherEvenementFinService(Liste_01 *evenements, int heure, int indiceVehicule, int indiceAppel);
void traiterEvenementFinService(Liste_01 *evenements, Appels *appels, Flotte *flotte, Matrice *dureeTrajet, int *tempsTotalDeplacementVehicules);
void declancherEvenementRetourDepot(Liste_01 *evenements, int heure, int indiceVehicule);
void traiterEvenementRetourDepot(Liste_01 *evenements, FileAttente *fileAttente, Flotte *flotte, Matrice *dureeTrajet, int *tempsTotalDeplacementVehicules);
void declancherEvenementFinRecharge(Liste_01 *evenements, int heure, int indiceVehicule);
void traiterEvenementFinRecharge(Liste_01 *evenements, Flotte *flotte, int *nombreRechargesEffectuees);
int rechercherVehicule(Flotte *flotte, int indiceAppel, Appels *appels, Matrice *dureeTrajet, int heure);
int estDisponible(Vehicule *vehicule, int indiceAppel, Appels *appels, Matrice *dureeTrajet, int heure);
int relu(int a);

#endif