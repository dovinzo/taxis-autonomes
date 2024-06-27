#include <stdio.h>
#include <stdlib.h>
#include "../include/flotte.h"

void lireFichierFlotte(Flotte *flotte, char const *nomFichier)
{
	FILE *fichier = fopen(nomFichier, "r");
	if (NULL == fichier)
	{
		printf("Erreur : echec lors d'une ouverture de fichier\n");
		exit(EXIT_FAILURE);
	}
	fscanf(fichier, "%d %d %d %d\n", &(flotte->nbVehicules), &(flotte->horizonTemporel), &(flotte->autonomie), &(flotte->dureeRecharge));
	flotte->vehicules = (Vehicule*)malloc(flotte->nbVehicules*sizeof(Vehicule));
	if (NULL == flotte->vehicules)
	{
		printf("Erreur : echec lors d'une allocation dynamique de memoire\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0 ; i < flotte->nbVehicules ; i++)
	{
		flotte->vehicules[i].charge = 100;
		flotte->vehicules[i].statut = LIBRE;
		flotte->vehicules[i].autonomie = flotte->autonomie;
	}
	fclose(fichier);
}

void initialiserPositionInitialeFlotte(Flotte *flotte, Matrice *dureeTrajet)
{
	int *occupe = (int*)malloc(dureeTrajet->nombreLignes*sizeof(int));
	if (NULL == occupe)
	{
		printf("Erreur : echec lors d'une allocation dynamique de memoire\n");
		exit(EXIT_FAILURE);
	}
	int emplacement;
	for (int i = 0 ; i < dureeTrajet->nombreLignes ; i++)
		occupe[i] = 0;
	flotte->vehicules[0].emplacement = 1;
	occupe[0] = 1;
	for (int i = 1 ; i < flotte->nbVehicules ; i++)
	{
		int max = -1;
		for (int j = 0 ; j < dureeTrajet->nombreLignes ; j++)
		{
			if (!occupe[j])
			{
				int somme = 0;
				for (int k = 0 ; k < i ; k++)
				{
					somme += getElementMatrice(dureeTrajet, j+1, flotte->vehicules[k].emplacement);
				}
				if (max < somme)
				{
					max = somme;
					emplacement = j+1;
				}
			}
		}
		flotte->vehicules[i].emplacement = emplacement;
		occupe[emplacement-1] = 1;
	}
	free(occupe);
}

void afficherPositionInitialeFlotte(Flotte *flotte)
{
	printf("Positions:");
	for (int i = 0 ; i < flotte->nbVehicules ; i++)
	{
		printf(" %d", flotte->vehicules[i].emplacement);
	}
	printf("\n");
}

void imprimerPositionInitialeFlotte(Flotte *flotte, FILE *fichier)
{
	fprintf(fichier, "Positions:");
	for (int i = 0 ; i < flotte->nbVehicules ; i++)
	{
		fprintf(fichier, " %d", flotte->vehicules[i].emplacement);
	}
	fprintf(fichier, "\n");
}

void libererFlotte(Flotte *flotte)
{
	free(flotte->vehicules);
	flotte->vehicules = NULL;
	flotte->autonomie = 0;
	flotte->dureeRecharge = 0;
	flotte->nbVehicules = 0;
}