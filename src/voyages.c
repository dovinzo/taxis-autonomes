#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/voyages.h"
#include "../include/liste_02.h"
#include "../include/matrice.h"
#include "../include/graphe.h"
#include "../include/appels.h"

void lireVoyages(Voyages *voyages, Appels *appels)
{
	voyages->nbVoyages = appels->nbAppels;
	voyages->voyages = (Voyage*)malloc(voyages->nbVoyages *sizeof(Voyage));
	if (NULL == voyages->voyages)
	{
		printf("Erreur : echec lors d'une allocation dynamique de memoire\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0 ; i < voyages->nbVoyages ; i++)
	{
		voyages->voyages[i].heure = appels->appels[i].heure;
		strcpy(voyages->voyages[i].nomClient, appels->appels[i].nomClient);
	}
}

void lireDureeTrajetVoyages(Voyages *voyages, Matrice *dureeTrajet, Graphe *reseauRoutier, Appels *appels)
{
	Element_02 element;
	Matrice predecesseur;
	creerMatrice(&predecesseur, dureeTrajet->nombreLignes, dureeTrajet->nombreColonnes);
	for (int sdeb = 0 ; sdeb < dureeTrajet->nombreLignes ; sdeb++)
	{
		dijkstra(reseauRoutier, sdeb, dureeTrajet, &predecesseur);
	}
	for (int i = 0 ; i < voyages->nbVoyages ; i++)
	{
		voyages->voyages[i].duree = getElementMatrice(dureeTrajet, appels->appels[i].origine, appels->appels[i].destination);
		
		element.sommet = appels->appels[i].destination;
		listeVide_02(&(voyages->voyages[i].itineraire));
		insererDebutListe_02(&(voyages->voyages[i].itineraire), &element);
		while (getElementMatrice(&predecesseur, appels->appels[i].origine, element.sommet) >= 0)
		{
			element.sommet = getElementMatrice(&predecesseur, appels->appels[i].origine, element.sommet)+1;
			insererDebutListe_02(&(voyages->voyages[i].itineraire), &element);
		}
	}
	libererMatrice(&predecesseur);
}

void triFusionVoyages(Voyage *voyages, int debut, int fin)
{
	int milieu;

	if (debut < fin)
	{
		milieu = (debut+fin)/2;
		triFusionVoyages(voyages, debut, milieu);
		triFusionVoyages(voyages, milieu+1, fin);
		fusionnerVoyages(voyages, debut, milieu, fin);
	}
}

void fusionnerVoyages(Voyage *voyages, int debut, int milieu, int fin)
{
	int i, j, k;
	Voyage *voyagesAux = (Voyage*)malloc((fin-debut+1)*sizeof(Voyage));
	if (NULL == voyagesAux)
	{
		printf("Erreur : echec lors d'une allocation dynamique de memoire\n");
		exit(EXIT_FAILURE);
	}
	i = debut;
	j = milieu+1;
	k = 0;
	while (i <= milieu && j <= fin)
	{
		if ((voyages[i].duree > voyages[j].duree) || (voyages[i].duree == voyages[j].duree && voyages[i].heure <= voyages[j].heure))
		{
			voyagesAux[k] = voyages[i];
			i++;
		}
		else
		{
			voyagesAux[k] = voyages[j];
			j++;
		}
		k++;
	}
	if (i > milieu)
		for (; j <= fin ; j++)
		{
			voyagesAux[k] = voyages[j];
			k++;
		}
	else
		for (; i <= milieu ; i++)
		{
			voyagesAux[k] = voyages[i];
			k++;
		}
	memcpy(voyages+debut,voyagesAux,(fin-debut+1)*sizeof(Voyage));
	free(voyagesAux);
}

void afficherVoyages(Voyages *voyages)
{
	printf("Voyages:\n");
	for (int i = 0 ; i < voyages->nbVoyages ; i++)
	{
		printf("%d %s %d", voyages->voyages[i].heure, voyages->voyages[i].nomClient, voyages->voyages[i].duree);
		Noeud_02 *j = voyages->voyages[i].itineraire.premier;
		while (NULL != j)
		{
			printf(" %d", j->element.sommet);
			j = j->suivant;
		}
		printf("\n");
	}
}

void imprimerVoyages(Voyages *voyages, FILE *fichier) // A MODIFIER
{
	fprintf(fichier, "Voyages:\n");
	for (int i = 0 ; i < voyages->nbVoyages ; i++)
	{
		fprintf(fichier, "%d %s %d", voyages->voyages[i].heure, voyages->voyages[i].nomClient, voyages->voyages[i].duree);
		Noeud_02 *j = voyages->voyages[i].itineraire.premier;
		while (NULL != j)
		{
			fprintf(fichier, " %d", j->element.sommet);
			j = j->suivant;
		}
		fprintf(fichier, "\n");
	}
}

void libererVoyages(Voyages *voyages)
{
	for (int i = 0 ; i < voyages->nbVoyages ; i++)
	{
		libererListe_02(&(voyages->voyages[i].itineraire));
	}
	free(voyages->voyages);
	voyages->voyages = NULL;
	voyages->nbVoyages = 0;
}