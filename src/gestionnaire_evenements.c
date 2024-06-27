#include "../include/gestionnaire_evenements.h"
#include "../include/liste_01.h"
#include "../include/appels.h"
#include "../include/element_01.h"
#include "../include/flotte.h"

void initialiserEvenements(Liste_01 *evenements, Appels *appels)
{
	Element_01 element;

	listeVide_01(evenements);

	for (int i = 0 ; i < appels->nbAppels ; i++)
	{
		element.evenement.type = APPEL;
		element.evenement.EvenementAppel.indiceAppel = i;
		//element.evenement.heureCreation = appels->appels[i].heure;
		element.evenement.heure = appels->appels[i].heure;
		
		insererDebutListe_01(evenements, &element);
	}

	triRapideListe_01(evenements->premier, evenements->dernier);
}

void traiterEvenement(Liste_01 *evenements, Appels *appels, Flotte *flotte, Matrice *dureeTrajet, FileAttente *fileAttente, int *nombreAppelsRefuses, int *nombreRechargesEffectuees, int *tempsTotalDeplacementVehicules, int *beneficeTotal)
{
	switch (evenements->premier->element.evenement.type)
	{
		case APPEL:
			traiterEvenementAppel(evenements, flotte, appels, dureeTrajet, nombreAppelsRefuses, beneficeTotal);
			printf("%d APPEL 0 %s\n", evenements->premier->element.evenement.heure, appels->appels[evenements->premier->element.evenement.EvenementAppel.indiceAppel].nomClient);
			break;
		
		case FIN_SERVICE:
			traiterEvenementFinService(evenements, appels, flotte, dureeTrajet, tempsTotalDeplacementVehicules);
			printf("%d FIN SERVICE %d %s\n", evenements->premier->element.evenement.heure, evenements->premier->element.evenement.EvenementFinService.indiceVehicule+1, appels->appels[evenements->premier->element.evenement.EvenementFinService.indiceAppel].nomClient);
			break;

		case RETOUR_DEPOT:
			traiterEvenementRetourDepot(evenements, fileAttente, flotte, dureeTrajet, tempsTotalDeplacementVehicules);
			printf("%d RETOUR DEPOT %d\n", evenements->premier->element.evenement.heure, evenements->premier->element.evenement.EvenementRetourDepot.indiceVehicule+1);
			break;

		case FIN_RECHARGE:
			traiterEvenementFinRecharge(evenements, flotte, nombreRechargesEffectuees);
			printf("%d FIN RECHARGE %d\n", evenements->premier->element.evenement.heure, evenements->premier->element.evenement.EvenementFinRecharge.indiceVehicule+1);
			break;
	}

	supprimerDebutListe_01(evenements);
}

void traiterEvenementAppel(Liste_01 *evenements, Flotte *flotte, Appels *appels, Matrice *dureeTrajet, int *nombreAppelsRefuses, int *beneficeTotal)
{
	int heure, dt1, dt2, dt, indiceAppel, indiceVehicule;

	heure = evenements->premier->element.evenement.heure;
	indiceAppel = evenements->premier->element.evenement.EvenementAppel.indiceAppel;
	indiceVehicule = rechercherVehicule(flotte,indiceAppel,appels,dureeTrajet,heure);

	if (indiceVehicule >= 0)
	{
		dt1 = getElementMatrice(dureeTrajet, flotte->vehicules[indiceVehicule].emplacement, appels->appels[indiceAppel].origine);
		dt2 = getElementMatrice(dureeTrajet,appels->appels[indiceAppel].origine,appels->appels[indiceAppel].destination);
		dt = dt1+relu(appels->appels[indiceAppel].heureMinimale-(heure+dt1))+dt2;

		declancherEvenementFinService(evenements, heure+dt, indiceVehicule, indiceAppel);
		flotte->vehicules[indiceVehicule].statut = OCCUPE;

		*beneficeTotal = *beneficeTotal+dt2;
		if (relu(appels->appels[indiceAppel].heureMinimale-(heure+dt1)) > 0)
		{
			*beneficeTotal = *beneficeTotal+appels->appels[indiceAppel].prime;
		}
	}
	else
	{
		*nombreAppelsRefuses = *nombreAppelsRefuses+1;
	}
}

void declancherEvenementFinService(Liste_01 *evenements, int heure, int indiceVehicule, int indiceAppel)
{
	Element_01 element;

	element.evenement.type = FIN_SERVICE;
	element.evenement.heure = heure;
	element.evenement.EvenementFinService.indiceVehicule = indiceVehicule;
	element.evenement.EvenementFinService.indiceAppel = indiceAppel;

	insererListe_01(evenements, &element);
}

void traiterEvenementFinService(Liste_01 *evenements, Appels *appels, Flotte *flotte, Matrice *dureeTrajet, int *tempsTotalDeplacementVehicules)
{
	int indiceAppel, indiceVehicule, dt1, dt2, dt3, dt, heure;

	heure = evenements->premier->element.evenement.heure;
	indiceAppel = evenements->premier->element.evenement.EvenementFinService.indiceAppel;
	indiceVehicule = evenements->premier->element.evenement.EvenementFinService.indiceVehicule;
	dt1 = getElementMatrice(dureeTrajet, flotte->vehicules[indiceVehicule].emplacement, appels->appels[indiceAppel].origine);
	dt2 = relu(appels->appels[indiceAppel].heureMinimale-(heure+dt1));
	dt3 = getElementMatrice(dureeTrajet,appels->appels[indiceAppel].origine,appels->appels[indiceAppel].destination);
	dt = dt1+dt2+dt3;

	flotte->vehicules[indiceVehicule].statut = LIBRE;
	flotte->vehicules[indiceVehicule].emplacement = appels->appels[indiceAppel].destination;
	flotte->vehicules[indiceVehicule].charge -= 100*(dt1+dt3)/flotte->vehicules[indiceVehicule].autonomie;

	if (flotte->vehicules[indiceVehicule].charge < 20)
	{
		flotte->vehicules[indiceVehicule].statut = OCCUPE;
		dt = getElementMatrice(dureeTrajet, flotte->vehicules[indiceVehicule].emplacement, 1);
		declancherEvenementRetourDepot(evenements, heure+dt, indiceVehicule);
	}

	*tempsTotalDeplacementVehicules = *tempsTotalDeplacementVehicules+dt1+dt3;
}

void declancherEvenementRetourDepot(Liste_01 *evenements, int heure, int indiceVehicule)
{
	Element_01 element;

	element.evenement.type = RETOUR_DEPOT;
	element.evenement.heure = heure;
	element.evenement.EvenementRetourDepot.indiceVehicule = indiceVehicule;

	insererListe_01(evenements, &element);
}

void traiterEvenementRetourDepot(Liste_01 *evenements, FileAttente *fileAttente, Flotte *flotte, Matrice *dureeTrajet, int *tempsTotalDeplacementVehicules)
{
	int heure_debut, heure_fin, dt;

	dt = getElementMatrice(dureeTrajet, flotte->vehicules[evenements->premier->element.evenement.EvenementRetourDepot.indiceVehicule].emplacement, 1);

	flotte->vehicules[evenements->premier->element.evenement.EvenementRetourDepot.indiceVehicule].emplacement = 1; // Le véhicule se trouve au dépôt

	// On place le véhicule dans la file d'attente
	fileAttente->nbVehicules++;
	if (fileAttente->nbVehicules == 1)
		fileAttente->tempsRechargeResiduelle = flotte->dureeRecharge;

	// On prédit la fin du chargement
	heure_debut = evenements->premier->element.evenement.heure;
	heure_fin = heure_debut + fileAttente->tempsRechargeResiduelle + (fileAttente->nbVehicules-1)*flotte->dureeRecharge;

	// On déclanche l'évènement fin de recharge
	declancherEvenementFinRecharge(evenements, heure_fin, evenements->premier->element.evenement.EvenementRetourDepot.indiceVehicule);

	// On compte le temps de déplacement du véhicule de la position finale au dépôt
	*tempsTotalDeplacementVehicules = *tempsTotalDeplacementVehicules+dt;
}

void declancherEvenementFinRecharge(Liste_01 *evenements, int heure, int indiceVehicule)
{
	Element_01 element;

	element.evenement.type = FIN_RECHARGE;
	element.evenement.heure = heure;
	element.evenement.EvenementFinRecharge.indiceVehicule = indiceVehicule;

	insererListe_01(evenements, &element);
}

void traiterEvenementFinRecharge(Liste_01 *evenements, Flotte *flotte, int *nombreRechargesEffectuees)
{
	flotte->vehicules[evenements->premier->element.evenement.EvenementFinRecharge.indiceVehicule].statut = LIBRE;
	*nombreRechargesEffectuees = *nombreRechargesEffectuees+1;
}

int estDisponible(Vehicule *vehicule, int indiceAppel, Appels *appels, Matrice *dureeTrajet, int heure)
{
	int t1 = getElementMatrice(dureeTrajet, vehicule->emplacement, appels->appels[indiceAppel].origine);
	int t2 = getElementMatrice(dureeTrajet,appels->appels[indiceAppel].origine,appels->appels[indiceAppel].destination);
	int t3 = getElementMatrice(dureeTrajet,appels->appels[indiceAppel].destination,1);
	if (vehicule->statut == LIBRE)
	{
		if (t1+relu(appels->appels[indiceAppel].heureMinimale-(heure+t1))+t2 <= appels->appels[indiceAppel].heureMaximale)
		{
			if (100*(t1+t2+t3)/vehicule->autonomie <= vehicule->charge)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

int relu(int a)
{
	return a > 0 ? a : 0;
}

int rechercherVehicule(Flotte *flotte, int indiceAppel, Appels *appels, Matrice *dureeTrajet, int heure)
{
	int j = -1;
	for (int i = 0 ; i < flotte->nbVehicules ; i++)
	{
		if (estDisponible(flotte->vehicules+i, indiceAppel, appels, dureeTrajet, heure))
		{
			if (j == -1)
			{
				j = i;
			}
			else
			{
				int tj = getElementMatrice(dureeTrajet, flotte->vehicules[j].emplacement, appels->appels[indiceAppel].origine);
				int ti = getElementMatrice(dureeTrajet, flotte->vehicules[i].emplacement, appels->appels[indiceAppel].origine);
				if (tj+relu(appels->appels[indiceAppel].heureMinimale-(heure+tj)) > ti+relu(appels->appels[indiceAppel].heureMinimale-(heure+ti)))
				{
					j = i;
				}
				else if (tj+relu(appels->appels[indiceAppel].heureMinimale-(heure+tj)) == ti+relu(appels->appels[indiceAppel].heureMinimale-(heure+ti)))
				{
					if (tj < ti)
					{
						j = i;
					}
				}
			}
		}
	}
	return j;
}