/********************************************************
*                                                       *
*    PROJECT: DS1307 library for weather station        *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 12/07/2022                                   *
*                                                       *
*********************************************************/

// Librairie de base de arduino
#include <Arduino.h>

// Déclaration de la structure permettant la lecture des donéees
struct MyTime {
    int secondes;
    int minutes;
    int hours;
    int day;
    int date;
    int month;
    int year;
};       

// Déclaration de la classe
class DS1307
{
    public: // Déclaration des variables et fonctions publiques
        DS1307(); // Constructeur
        ~DS1307(); // Déstructeur

        // Déclaration des fonctions publiques
        void begin(); 
        void setupRealTime(struct tm *time); 
        void getRealTime(struct MyTime *myTm);
        

    private: // Déclaration des variables et fonctions privées
        // Déclaration des fonctions privées
        uint8_t decToBcd(uint8_t dec);
        uint8_t bcdToDec(uint8_t bcd);
        int actualYear(int yearsFrom1900);
};