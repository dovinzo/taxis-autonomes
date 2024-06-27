// include/element_01.h
#ifndef ELEMENT_01_H
#define ELEMENT_01_H

#include "evenement.h"

typedef struct {
	Evenement evenement;
}Element_01;

int relationOrdreElement_01(Element_01 element1, Element_01 element2);

#endif