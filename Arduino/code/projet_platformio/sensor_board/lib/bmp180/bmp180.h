/********************************************************
*                                                       *
*    PROJECT: BMP180 library for weather station        *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 12/07/2022                                   *
*                                                       *
*********************************************************/

// Librairie de base de arduino
#include <Arduino.h>

// Déclaration de la classe
class BMP180
{
    public: // Déclaration des variables et fonctions publiques
        BMP180(); // Constructeur
        ~BMP180(); // Déstructeur

        // Déclaration des fonctions publiques
        long getPressure();
        void begin();

    private:// Déclaration des variables et fonctions privées
        // Déclaration des fonctions privées
        int32_t readPressure();
		int32_t readTemp();
        long convertRawPressure(int32_t rawPressure);
        int32_t read2SignedByte(int8_t addr);
        uint32_t read2UnsignedByte(int8_t addr);
        
        // Déclaration des variables privées
        int16_t _ac1 = 0, _ac2 = 0, _ac3 = 0, _b1 = 0, _b2 = 0, _mb = 0, _mc = 0, _md = 0, _oss = 0;
        uint16_t _ac4 = 0, _ac5 = 0, _ac6 = 0;
        int32_t _x1 = 0, _x2 = 0, _x3 = 0, _b3 = 0, _b5 = 0, _b6 = 0, _b7  = 0;
        uint32_t _b4 = 0;
};
