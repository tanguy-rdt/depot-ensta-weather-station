/********************************************************
*                                                       *
*    PROJECT: Si7034 library for weather station        *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 12/07/2022                                   *
*                                                       *
*********************************************************/

// Librairies de base à arduino
#include <Arduino.h>

// Déclaration de la classe
class SI7034
{
    public: // Déclaration des variables et fonctions publiques
        SI7034();// Constructeur
        ~SI7034(); // Déstructeur

        // Déclaration des fonctions publiques
        void begin();
        void startMesurement();
        float getTemp();
        float getRH();

    private: // Déclaration des variables et fonctions privées
        // Déclaration des fonctions privées
        uint16_t readRawTemp();
        uint16_t readRawRh();
        float convertRawTemp(uint16_t rawTemp);
        float convertRawRH(uint16_t rawRH);

        // Déclaration des variables privées
        uint16_t _rawRH = 0, _rawTemp = 0;
};


