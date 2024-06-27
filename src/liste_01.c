#include <stdlib.h>
#include <stdio.h>
#include "../include/liste_01.h"

void listeVide_01(Liste_01 *liste)
{
	liste->premier = NULL;
	liste->dernier = NULL;
}

int estVideListe_01(Liste_01 *liste)
{
	return NULL == liste->premier;
}

void insererDebutListe_01(Liste_01 *liste, Element_01 *element)
{
	Noeud_01 *noeud = (Noeud_01*)malloc(sizeof(Noeud_01));
	if (NULL == noeud)
	{
		printf("Erreur : echec lors d'une allocation dynamique de memoire\n");
		exit(EXIT_FAILURE);
	}
	noeud->element = *element;
	noeud->precedent = NULL;
	noeud->suivant = liste->premier;
	if (!estVideListe_01(liste))
	{
		liste->premier->precedent = noeud;
	}
	else
	{
		liste->dernier = noeud;
	}
	liste->premier = noeud;
}

void supprimerDebutListe_01(Liste_01 *liste)
{
	Noeud_01 *noeudASupprimer;

	if (!estVideListe_01(liste))
	{
		noeudASupprimer = liste->premier;
		liste->premier = liste->premier->suivant;
		free(noeudASupprimer);
		if (!estVideListe_01(liste))
			liste->premier->precedent = NULL;
		else
			liste->dernier = NULL;
	}
}

void insererListe_01(Liste_01 *liste, Element_01 *element)
{
	Noeud_01 *noeudActuel;
	Noeud_01 *noeudPrecedent;

	Noeud_01 *noeud = (Noeud_01*)malloc(sizeof(Noeud_01));
	if (NULL == noeud)
	{
		printf("Erreur : echec lors d'une allocation dynamique de memoire\n");
		exit(EXIT_FAILURE);
	}
	noeud->element = *element;

	if (estVideListe_01(liste))
	{
		noeud->precedent = NULL;
		noeud->suivant = NULL;
		liste->premier = noeud;
		liste->dernier = noeud;
	}

	else if (relationOrdreElement_01(noeud->element,liste->premier->element))
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
		while (NULL != noeudActuel && !relationOrdreElement_01(noeud->element,noeudActuel->element))
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

void libererListe_01(Liste_01 *liste)
{
	Noeud_01 *noeudASupprimer;

	while (NULL != liste->premier)
	{
		noeudASupprimer = liste->premier;
		liste->premier = liste->premier->suivant;
		free(noeudASupprimer);
	}
	
	liste->dernier = NULL;
}

void triRapideListe_01(Noeud_01 *premier, Noeud_01 *dernier)
{
	Noeud_01 *pivot;

	if (NULL != premier && NULL != dernier && premier != dernier)
	{
		pivot = choixPivotListe_01(premier, dernier);
		pivot = partitionnerListe_01(premier, dernier, pivot);
		if (premier == pivot)
			triRapideListe_01(premier, NULL);
		else
			triRapideListe_01(premier, pivot->precedent);
		if (dernier == pivot)
			triRapideListe_01(NULL, dernier);
		else
			triRapideListe_01(pivot->suivant, dernier);
	}
}

Noeud_01 *choixPivotListe_01(Noeud_01 *premier, Noeud_01 *dernier)
{
	return dernier;
}

Noeud_01 *partitionnerListe_01(Noeud_01 *premier, Noeud_01 *dernier, Noeud_01 *pivot)
{
	Noeud_01 *i;
	Noeud_01 *j;

	echangerListe_01(pivot, dernier);
	j = premier;
	i = premier;
	while (i != dernier)
	{
		if (relationOrdreElement_01(i->element,dernier->element))
		{
			echangerListe_01(i, j);
			j = j->suivant;
		}
		i = i->suivant;
	}
	echangerListe_01(dernier, j);
	return j;
}

void echangerListe_01(Noeud_01 *i, Noeud_01 *j)
{
	Element_01 auxElement;

	auxElement = i->element;
	i->element = j->element;
	j->element = auxElement;
}