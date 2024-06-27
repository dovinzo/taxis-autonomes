// include/file_attente.h
#ifndef FILE_ATTENTE_H
#define FILE_ATTENTE_H

typedef struct {
	int nbVehicules;
	int tempsRechargeResiduelle;
}FileAttente;

void initialiserFileAttente(FileAttente *fileAttente);
void miseAJourFileAttente(FileAttente *fileAttente, int heure_avant, int heure_apres, int dureeRecharge);

#endif