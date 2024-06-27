#include <stdio.h>
#include <stdlib.h>
#include "include/appels.h"
#include "include/clients.h"
#include "include/flotte.h"
#include "include/voyages.h"
#include "include/graphe.h"
#include "include/liste_01.h"
#include "include/matrice.h"
#include "include/file_attente.h"
#include "include/gestionnaire_evenements.h"

typedef struct {
    Appels appels;
    Voyages voyages;
    Graphe reseauRoutier;
    Clients clients;
    Liste_01 evenements;
    Flotte flotte;
    Matrice dureeTrajet;
    FileAttente fileAttente;
    int horloge; // Pour stocker l'heure d'avant
    int nombreAppelsRefuses;
    int nombreRechargesEffectuees;
    int tempsTotalDeplacementVehicules;
    int beneficeTotal;
}Donnees;

int main(int argc, char const *argv[])
{
    Donnees donnees;

    if (argc != 4)
    {
        printf("Erreur : nombre d'arguments incorrect\nVoici un exemple : nom_programme fichier_réseau_routier fichier_flotte fichier_appels\n");
		exit(EXIT_FAILURE);
    }

    /*********************************************************************************
     **************************** Initialisation des données *************************
     *********************************************************************************/

    lireFichierAppels(&(donnees.appels), argv[3]);
    lireFichierGraphe(&(donnees.reseauRoutier), argv[1]);
    lireVoyages(&(donnees.voyages), &(donnees.appels));

    creerMatrice(&(donnees.dureeTrajet), donnees.reseauRoutier.nombreSommets, donnees.reseauRoutier.nombreSommets);
    lireDureeTrajetVoyages(&(donnees.voyages), &(donnees.dureeTrajet), &(donnees.reseauRoutier), &(donnees.appels));
    triFusionVoyages(donnees.voyages.voyages, 0, donnees.voyages.nbVoyages-1);

    lireFichierFlotte(&(donnees.flotte), argv[2]);
    initialiserPositionInitialeFlotte(&(donnees.flotte), &(donnees.dureeTrajet));

    lireClients(&(donnees.clients), &(donnees.appels));
    triFusionClients(donnees.clients.clients, 0, donnees.clients.nbClients-1);

    initialiserEvenements(&(donnees.evenements), &(donnees.appels));

    initialiserFileAttente(&(donnees.fileAttente));

    donnees.horloge = 0;

    donnees.nombreAppelsRefuses = 0;

    donnees.nombreRechargesEffectuees = 0;

    donnees.tempsTotalDeplacementVehicules = 0;

    donnees.beneficeTotal = 0;

    /*******************************************************************************
     *************************** Affichage des clients *****************************
     *******************************************************************************/

    afficherClients(&(donnees.clients));

    /*******************************************************************************
     *************************** Affichage des voyages *****************************
     *******************************************************************************/

    afficherVoyages(&(donnees.voyages));

    /*******************************************************************************
     ********* Affichage de la position initiale des véhicules de la flotte ********
     *******************************************************************************/

    afficherPositionInitialeFlotte(&(donnees.flotte));

    /*******************************************************************************
     ******************************** Simulation ***********************************
     *******************************************************************************/

    printf("Evènements:\n");

    while (!estVideListe_01(&(donnees.evenements)))
    {
        miseAJourFileAttente(&(donnees.fileAttente), donnees.horloge, donnees.evenements.premier->element.evenement.heure, donnees.flotte.dureeRecharge);
        donnees.horloge = donnees.evenements.premier->element.evenement.heure;
        traiterEvenement(&(donnees.evenements), &(donnees.appels), &(donnees.flotte), &(donnees.dureeTrajet), &(donnees.fileAttente), &(donnees.nombreAppelsRefuses), &(donnees.nombreRechargesEffectuees), &(donnees.tempsTotalDeplacementVehicules), &(donnees.beneficeTotal));
    }

    /*******************************************************************************
     *************** Affichage de quelques informations récapitulatives*************
     *******************************************************************************/

    printf("Appels non desservis: %d\n", donnees.nombreAppelsRefuses);
    printf("Recharges: %d\n", donnees.nombreRechargesEffectuees);
    printf("Temps total: %d\n", donnees.tempsTotalDeplacementVehicules);
    printf("Bénéfice: %d\n", donnees.beneficeTotal);

    /*******************************************************************************
     ************************** Libération des données *****************************
     *******************************************************************************/

    libererAppels(&(donnees.appels));

    libererGraphe(&(donnees.reseauRoutier));

    libererVoyages(&(donnees.voyages));

    libererMatrice(&(donnees.dureeTrajet));

    libererFlotte(&(donnees.flotte));

    libererClients(&(donnees.clients));

    libererListe_01(&(donnees.evenements));

    return EXIT_SUCCESS;
}