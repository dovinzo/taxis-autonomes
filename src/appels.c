#include <stdio.h>
#include <stdlib.h>
#include "../include/appels.h"

void lireFichierAppels(Appels *appels, char const *nomFichier)
{
	FILE *fichier = fopen(nomFichier,"r");
	if (NULL == fichier)
	{
		printf("Erreur : echec lors d'une ouverture de fichier\n");
		exit(EXIT_FAILURE);
	}
	fscanf(fichier, "%d\n", &(appels->nbAppels));
	appels->appels = (Appel*)malloc(appels->nbAppels*sizeof(Appel));
	if (NULL == appels->appels)
	{
		printf("Erreur : echec lors d'une allocation dynamique de memoire\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0 ; i < appels->nbAppels ; i++)
	{
		fscanf(fichier, "%d %s %d %d %d %d %d\n", &(appels->appels[i].heure), appels->appels[i].nomClient, &(appels->appels[i].origine), &(appels->appels[i].destination), &(appels->appels[i].heureMinimale), &(appels->appels[i].heureMaximale), &(appels->appels[i].prime));
	}
	fclose(fichier);
}

void libererAppels(Appels *appels)
{
	free(appels->appels);
	appels->appels = NULL;
	appels->nbAppels = 0;
}