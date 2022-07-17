/********************************************************
*                                                       *
*    PROJECT: SHT21 library for weather station         *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 12/07/2022                                   *
*                                                       *
*********************************************************/

// Librairie de base de arduino
#include <Arduino.h>

// Déclaration de la classe
class SHT21
{
    public: // Déclaration des variables et fonctions publiques
     	SHT21(); // Constructeur
     	~SHT21(); // Déstructeur

        // Déclaration des fonctions publiques
        void begin();
        float getTemp();
        float getRH();

    private: // Déclaration des variables et fonctions privées
        // Déclaration des fonctions privées
        uint16_t readTemp();
        uint16_t readRH();
	    float convertRawTemp(uint16_t rawTemp);
	    float convertRawRH(uint16_t rawRH);
};
