/********************************************************
*                                                       *
*    PROJECT: SHT21 library for weather station         *
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
#include "sht21.h"

// Déclaration des addr
#define SHT21_ADDR                 0x40 

#define TEMP_CMD_NO_HOLD_ADDR      0xf3
#define RH_CMD_NO_HOLD_ADDR        0xf5


SHT21::SHT21() // Constructeur
{
}

SHT21::~SHT21() // Déstructeur
{
}

void SHT21::begin()
{
    Wire.begin(); // Initialisation de la lib Wire
}

// Fonction permettant de retourner la température en float
float SHT21::getTemp()
{
    uint16_t rawTemp = readTemp();
    float convertedTemp = convertRawTemp(rawTemp);

    return convertedTemp;
}

// Fonction permettant de retourner l'humidité en float
float SHT21::getRH()
{
    uint16_t rawRH = readRH();
    float convertedRH = convertRawRH(rawRH);

    return convertedRH;
}

// fonction permettant de lire la température brut
uint16_t SHT21::readTemp()
{
    Wire.beginTransmission(SHT21_ADDR);
    Wire.write(TEMP_CMD_NO_HOLD_ADDR);
    Wire.endTransmission();

    //delayMicroseconds(20); // delay de la datasheet mais ne fonctionne pas sous proteus, a voir sur carte
	delay(150); // delay au pif mais qui fonctionne

    Wire.requestFrom(SHT21_ADDR, 3);

    if (3 <= Wire.available()){
	uint8_t _msb = Wire.read();
	uint8_t _lsb = Wire.read();
    uint8_t _checksum = Wire.read();

	uint16_t _ret = _msb << 8 | _lsb;
	
	return _ret;
    }
	
	return -1; // retourne -1 s'il y a une err
}

// fonction permettant de lire l'humidité brut
uint16_t SHT21::readRH()
{
    Wire.beginTransmission(SHT21_ADDR);
    Wire.write(RH_CMD_NO_HOLD_ADDR);
    Wire.endTransmission();

    //delayMicroseconds(20); // delay de la datasheet mais ne fonctionne pas sous proteus, a voir sur carte
	delay(150); // delay au pif mais qui fonctionne

    Wire.requestFrom(SHT21_ADDR, 3);

    while (3 <= Wire.available()){
	uint8_t _msb = Wire.read();
	uint8_t _lsb = Wire.read();
    uint8_t _checksum = Wire.read();

	uint16_t _ret = _msb << 8 | _lsb;
	return _ret;
    }
	
	return -1; // retourne -1 s'il y a une err
}

// fonction permttant la convertion de la température de 16 bits à float
float SHT21::convertRawTemp(uint16_t _rawTemp)
{
    float _temp = -46.85 + 175.72*((float)_rawTemp/(pow(2,16)));
    return _temp;
}

// fonction permettant la conversion de l'humidité de 16 bits à float
float SHT21::convertRawRH(uint16_t _rawRH)
{
    float _rh = -6 + 125*((float)_rawRH/(pow(2,16)));
    return _rh;
}

