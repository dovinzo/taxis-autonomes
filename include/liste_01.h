// include/liste_01.h
#ifndef LISTE_01_H
#define LISTE_01_H

#include "element_01.h"

typedef struct Noeud_01 Noeud_01;
struct Noeud_01 {
	Element_01 element;
	Noeud_01 *precedent;
	Noeud_01 *suivant;
};

typedef struct {
	Noeud_01 *premier;
	Noeud_01* dernier;
}Liste_01;

void listeVide_01(Liste_01 *liste);
int estVideListe_01(Liste_01 *liste);
void insererDebutListe_01(Liste_01 *liste, Element_01 *element);
void supprimerDebutListe_01(Liste_01 *liste);
void insererListe_01(Liste_01 *liste, Element_01 *element);
void libererListe_01(Liste_01 *liste);
void triRapideListe_01(Noeud_01 *premier, Noeud_01 *dernier);
Noeud_01 *choixPivotListe_01(Noeud_01 *premier, Noeud_01 *dernier);
Noeud_01 *partitionnerListe_01(Noeud_01 *premier, Noeud_01 *dernier, Noeud_01 *pivot);
void echangerListe_01(Noeud_01 *i, Noeud_01 *j);

#endif