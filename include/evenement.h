// include/evenement.h
#ifndef EVENEMENT_H
#define EVENEMENT_H

typedef enum {
	APPEL,
	FIN_SERVICE,
	RETOUR_DEPOT,
	FIN_RECHARGE
}TypeEvenement;

typedef struct {
	TypeEvenement type;
	union {
		struct {
			int indiceAppel;
		}EvenementAppel;
		struct {
			int indiceVehicule;
			//char nomClient[25];
			//int destination;
			int indiceAppel;
		}EvenementFinService;
		struct {
			int indiceVehicule;
		}EvenementRetourDepot;
		struct {
			int indiceVehicule;
		}EvenementFinRecharge;
	};
	//int heureCreation;
	int heure;
}Evenement;

#endif