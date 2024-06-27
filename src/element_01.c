#include "../include/element_01.h"

int relationOrdreElement_01(Element_01 element1, Element_01 element2) // A MODIFIER
{
	int type1, type2;
	if (element1.evenement.heure < element2.evenement.heure)
		return 1;
	if (element1.evenement.heure == element2.evenement.heure)
	{
		switch (element1.evenement.type)
		{
			case FIN_RECHARGE:
				type1 = 1;
				break;
			case FIN_SERVICE:
				type1 = 2;
				break;
			case RETOUR_DEPOT:
				type1 = 3;
				break;
			case APPEL:
				type1 = 4;
				break;
		}
		switch (element2.evenement.type)
		{
			case FIN_RECHARGE:
				type2 = 1;
				break;
			case FIN_SERVICE:
				type2 = 2;
				break;
			case RETOUR_DEPOT:
				type2 = 3;
				break;
			case APPEL:
				type2 = 4;
				break;
		}
		return type1 <= type2;
	}
	return 0;
}