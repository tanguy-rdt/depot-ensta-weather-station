/********************************************************
*                                                       *
*    PROJECT: WebUI for weather station                 *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 12/07/2022                                   *
*                                                       *
*********************************************************/

// Librairie de base de arduino
#include <Arduino.h>

// Déclaration de la classe
class WEBUI
{
    public: // Déclaration des variables et fonctions publiques
        WEBUI();// Constructeur
        ~WEBUI(); // Déstructeur

        // Déclaration des fonctions publiques
        void begin();
        void displayValue();
        void setValue(float *inTemp, float *inRh, float *outTemp, float *outRh, long *Press, struct MyTime *myTm);
};


