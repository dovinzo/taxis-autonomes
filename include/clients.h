// include/clients.h
#ifndef CLIENTS_H
#define CLIENTS_H

typedef struct {
	char nomClient[25];
}Client;

typedef struct {
	int nbClients;
	Client *clients;
}Clients;

#include "appels.h"

void lireClients(Clients *clients, Appels *appels);
void triFusionClients(Client *clients, int debut, int fin);
void fusionnerClients(Client *clients, int debut, int milieu, int fin);
void afficherClients(Clients *clients);
void imprimerClients(Clients *clients, FILE *fichier);
void libererClients(Clients *clients);

#endif