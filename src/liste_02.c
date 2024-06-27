#include <stdlib.h>
#include <stdio.h>
#include "../include/liste_02.h"

void listeVide_02(Liste_02 *liste)
{
	liste->premier = NULL;
	liste->dernier = NULL;
}

int estVideListe_02(Liste_02 *liste)
{
	return NULL == liste->premier;
}

void insererDebutListe_02(Liste_02 *liste, Element_02 *element)
{
	Noeud_02 *noeud = (Noeud_02*)malloc(sizeof(Noeud_02));
	if (NULL == noeud)
	{
		printf("Erreur : echec lors d'une allocation dynamique de memoire\n");
		exit(EXIT_FAILURE);
	}
	noeud->element = *element;
	noeud->precedent = NULL;
	noeud->suivant = liste->premier;
	if (!estVideListe_02(liste))
		liste->premier->precedent = noeud;
	else
		liste->dernier = noeud;
	liste->premier = noeud;
}

void insererFinListe_02(Liste_02 *liste, Element_02 *element)
{
	Noeud_02 *noeud = (Noeud_02*)malloc(sizeof(Noeud_02));
	if (NULL == noeud)
	{
		printf("Erreur : echec lors d'une allocation dynamique de memoire\n");
		exit(EXIT_FAILURE);
	}
	noeud->element = *element;
	noeud->suivant = NULL;
	noeud->precedent = liste->dernier;
	if (!estVideListe_02(liste))
		liste->dernier->suivant = noeud;
	else
		liste->premier = noeud;
	liste->dernier = noeud;
}

void supprimerDebutListe_02(Liste_02 *liste)
{
	Noeud_02 *noeudASupprimer;

	if (!estVideListe_02(liste))
	{
		noeudASupprimer = liste->premier;
		liste->premier = liste->premier->suivant;
		free(noeudASupprimer);
		if (!estVideListe_02(liste))
			liste->premier->precedent = NULL;
		else
			liste->dernier = NULL;
	}
}

void insererListe_02(Liste_02 *liste, Element_02 *element)
{
	Noeud_02 *noeudActuel;
	Noeud_02 *noeudPrecedent;

	Noeud_02 *noeud = (Noeud_02*)malloc(sizeof(Noeud_02));
	if (NULL == noeud)
	{
		printf("Erreur : echec lors d'une allocation dynamique de memoire\n");
		exit(EXIT_FAILURE);
	}
	noeud->element = *element;

	if (estVideListe_02(liste))
	{
		noeud->precedent = NULL;
		noeud->suivant = NULL;
		liste->premier = noeud;
		liste->dernier = noeud;
	}

	else if (relationOrdreElement_02(noeud->element,liste->premier->element))
	{
		noeud->precedent = NULL;
		noeud->suivant = liste->premier;
		liste->premier->precedent = noeud;
		liste->premier = noeud;
	}

	else
	{
		noeudPrecedent = liste->premier;
		noeudActuel = liste->premier->suivant;
		while (NULL != noeudActuel && !relationOrdreElement_02(noeud->element,noeudActuel->element))
		{
			noeudPrecedent = noeudActuel;
			noeudActuel = noeudPrecedent->suivant;
		}
		if (NULL == noeudActuel)
		{
			noeudPrecedent->suivant = noeud;
			noeud->precedent = noeudPrecedent;
			noeud->suivant = NULL;
			liste->dernier = noeud;
		}
		else
		{
			noeudPrecedent->suivant = noeud;
			noeud->precedent = noeudPrecedent;
			noeud->suivant = noeudActuel;
			noeudActuel->precedent = noeud;
		}
	}
}

void libererListe_02(Liste_02 *liste)
{
	Noeud_02 *noeudASupprimer;

	while (NULL != liste->premier)
	{
		noeudASupprimer = liste->premier;
		liste->premier = liste->premier->suivant;
		free(noeudASupprimer);
	}
	
	liste->dernier = NULL;
}

void triRapideListe_02(Noeud_02 *premier, Noeud_02 *dernier)
{
	Noeud_02 *pivot;

	if (NULL != premier && NULL != dernier && premier != dernier)
	{
		pivot = choixPivotListe_02(premier, dernier);
		pivot = partitionnerListe_02(premier, dernier, pivot);
		if (premier == pivot)
			triRapideListe_02(premier, NULL);
		else
			triRapideListe_02(premier, pivot->precedent);
		if (dernier == pivot)
			triRapideListe_02(NULL, dernier);
		else
			triRapideListe_02(pivot->suivant, dernier);
	}
}

Noeud_02 *choixPivotListe_02(Noeud_02 *premier, Noeud_02 *dernier)
{
	return dernier;
}

Noeud_02 *partitionnerListe_02(Noeud_02 *premier, Noeud_02 *dernier, Noeud_02 *pivot)
{
	Noeud_02 *i;
	Noeud_02 *j;

	echangerListe_02(pivot, dernier);
	j = premier;
	i = premier;
	while (i != dernier)
	{
		if (relationOrdreElement_02(i->element,dernier->element))
		{
			echangerListe_02(i, j);
			j = j->suivant;
		}
		i = i->suivant;
	}
	echangerListe_02(dernier, j);
	return j;
}

void echangerListe_02(Noeud_02 *i, Noeud_02 *j)
{
	Element_02 auxElement;

	auxElement = i->element;
	i->element = j->element;
	j->element = auxElement;
}