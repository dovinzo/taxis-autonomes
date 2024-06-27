#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/clients.h"

void lireClients(Clients *clients, Appels *appels)
{
	clients->nbClients = appels->nbAppels;
	clients->clients = (Client*)malloc(clients->nbClients*sizeof(Client));
	if (NULL == clients->clients)
	{
		printf("Erreur : echec lors d'une allocation dynamique de memoire\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0 ; i < clients->nbClients ; i++)
	{
		strcpy(clients->clients[i].nomClient, appels->appels[i].nomClient);
	}
}

void triFusionClients(Client *clients, int debut, int fin)
{
	int milieu;

	if (debut < fin)
	{
		milieu = (debut+fin)/2;
		triFusionClients(clients, debut, milieu);
		triFusionClients(clients, milieu+1, fin);
		fusionnerClients(clients, debut, milieu, fin);
	}
}

void fusionnerClients(Client *clients, int debut, int milieu, int fin)
{
	int i, j, k;
	Client *clientsAux = (Client*)malloc((fin-debut+1)*sizeof(Client));
	if (NULL == clientsAux)
	{
		printf("Erreur : echec lors d'une allocation dynamique de memoire\n");
		exit(EXIT_FAILURE);
	}
	i = debut;
	j = milieu+1;
	k = 0;
	while (i <= milieu && j <= fin)
	{
		if (strcmp(clients[i].nomClient, clients[j].nomClient) <= 0)
		{
			strcpy(clientsAux[k].nomClient, clients[i].nomClient);
			i++;
		}
		else
		{
			strcpy(clientsAux[k].nomClient, clients[j].nomClient);
			j++;
		}
		k++;
	}
	if (i > milieu)
		for (; j <= fin ; j++)
		{
			strcpy(clientsAux[k].nomClient, clients[j].nomClient);
			k++;
		}
	else
		for (; i <= milieu ; i++)
		{
			strcpy(clientsAux[k].nomClient, clients[i].nomClient);
			k++;
		}
	memcpy(clients+debut,clientsAux,(fin-debut+1)*sizeof(Client));
	free(clientsAux);
}

void afficherClients(Clients *clients)
{
	printf("Clients:\n");
	for (int i = 0 ; i < clients->nbClients ; i++)
	{
		printf("%s\n", clients->clients[i].nomClient);
	}
}

void imprimerClients(Clients *clients, FILE *fichier)
{
	fprintf(fichier, "Clients:\n");
	for (int i = 0 ; i < clients->nbClients ; i++)
	{
		fprintf(fichier, "%s\n", clients->clients[i].nomClient);
	}
}

void libererClients(Clients *clients)
{
	free(clients->clients);
	clients->clients = NULL;
	clients->nbClients = 0;
}