#include "../include/file_attente.h"

void initialiserFileAttente(FileAttente *fileAttente)
{
    fileAttente->nbVehicules = 0;
    fileAttente->tempsRechargeResiduelle = 0;
}

void miseAJourFileAttente(FileAttente *fileAttente, int heure_avant, int heure_apres, int dureeRecharge)
{
    int dt = heure_apres-heure_avant;

    if (fileAttente->nbVehicules > 0)
    {
        if (dt < fileAttente->tempsRechargeResiduelle)
            fileAttente->tempsRechargeResiduelle -= dt;
        else
        {
            dt -= fileAttente->tempsRechargeResiduelle;
            fileAttente->nbVehicules--;
            while (dt > dureeRecharge && fileAttente->nbVehicules > 0)
            {
                fileAttente->nbVehicules--;
                dt -= dureeRecharge;
            }
            if (fileAttente->nbVehicules > 0)
                fileAttente->tempsRechargeResiduelle = dt;
            else
                fileAttente->tempsRechargeResiduelle = 0;
        }
    }
}