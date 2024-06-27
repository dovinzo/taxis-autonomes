// include/liste_02.h
#ifndef LISTE_02_H
#define LISTE_02_H

#include "element_02.h"

typedef struct Noeud_02 Noeud_02;
struct Noeud_02 {
	Element_02 element;
	Noeud_02 *precedent;
	Noeud_02 *suivant;
};

typedef struct {
	Noeud_02 *premier;
	Noeud_02* dernier;
}Liste_02;

void listeVide_02(Liste_02 *liste);
int estVideListe_02(Liste_02 *liste);
void insererDebutListe_02(Liste_02 *liste, Element_02 *element);
void insererFinListe_02(Liste_02 *liste, Element_02 *element);
void supprimerDebutListe_02(Liste_02 *liste);
void insererListe_02(Liste_02 *liste, Element_02 *element);
void libererListe_02(Liste_02 *liste);
void triRapideListe_02(Noeud_02 *premier, Noeud_02 *dernier);
Noeud_02 *choixPivotListe_02(Noeud_02 *premier, Noeud_02 *dernier);
Noeud_02 *partitionnerListe_02(Noeud_02 *premier, Noeud_02 *dernier, Noeud_02 *pivot);
void echangerListe_02(Noeud_02 *i, Noeud_02 *j);

#endif