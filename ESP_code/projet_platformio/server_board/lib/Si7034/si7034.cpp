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
#include <Wire.h>
#include <time.h>

// Déclaration du .h de la librairie
#include "si7034.h"

// Déclaration des addr
#define SI7034_ADDR               0x70 // adrr de l'esclave i2c

#define TEMP_MES_NH_NMODE         0x78
#define RH_MES_NH_NMODE           0x66


SI7034::SI7034() // Constructeur
{
}

SI7034::~SI7034() // Destructeur
{
}

void SI7034::begin() // Initialisation du Si7034
{
    Wire.begin(); // Initialisation de la lib Wire
}


float SI7034::getTemp() // Fonction permettant de retourner la température
{
    uint16_t rawTemp = readRawTemp();
    float temp = convertRawTemp(rawTemp);

    return temp;
}

float SI7034::getRH() // Fonction permettant de retourner l'humidité
{
    uint16_t rawRh = readRawRh();
    float rh = convertRawTemp(rawRh);

    return rh;
}

uint16_t SI7034::readRawTemp()
{ // Fonction de permttant de lire les registres de température
    Wire.beginTransmission(SI7034_ADDR);
    Wire.write(TEMP_MES_NH_NMODE); // On dis qu'on veut lire à l'adresse des registres de température
    Wire.endTransmission();

    delay(70); // temps d'att de la fin de lecture

    Wire.requestFrom(SI7034_ADDR, 2); // Requette de lecture de 2 octets

    if (2 <= Wire.available()) // On att les deux octets
    {
        uint8_t _msb = Wire.read(); // Lecture du premier octet 
        uint8_t _lsb = Wire.read(); // Lecture du second octet 

        return ((_msb << 8) | (_lsb)); // Concaténation pour obtenir une valeur sur 16 bit
    }

    return -1; // si err on retourne -1
}


uint16_t SI7034::readRawRh()
{ // Fonction permettant de lire les registres d'humidité
    Wire.beginTransmission(SI7034_ADDR);
    Wire.write(RH_MES_NH_NMODE);
    Wire.endTransmission();

    delay(70);

    Wire.requestFrom(SI7034_ADDR, 2);

    if (2 <= Wire.available())
    {
        uint8_t _msb = Wire.read();
        uint8_t _lsb = Wire.read();

        return ((_msb << 8) | (_lsb));
    }

    return -1;
}

// Fonction permettant la conversion de la température brut (16 bits) en float
float SI7034::convertRawTemp(uint16_t rawTemp)
{
    return -45 + 175 * ((rawTemp)/pow(2, 16));
}

// Fonction permettant la conversion de l'humidité brut (16 bits) en float
float SI7034::convertRawRH(uint16_t rawRH)
{
    return 100 * ((rawRH)/pow(2, 16));
}