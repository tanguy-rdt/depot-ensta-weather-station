/********************************************************
*                                                       *
*    PROJECT: SHT21 library for weather station         *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 29/06/2022                                   *
*                                                       *
*********************************************************/


#include <Arduino.h>
#include <Wire.h>
#include <time.h>

#include "sht21.h"

#define SHT21_ADDR                 0x40 // utiliser cette addr sur proteus et peut-être la carte aussi

#define SHT21_ADDR_W               0x80 // addr de la datasheet mais ne fonctionne pas sur proteus, a voir sur carte
#define SHT21_ADDR_R               0x81 // addr de ...

#define TEMP_CMD_NO_HOLD_ADDR      0xf3
#define RH_CMD_NO_HOLD_ADDR        0xf5


SHT21::SHT21()
{
}

void SHT21::begin()
{
    Wire.begin();
}

float SHT21::getTemp()
{
    uint16_t rawTemp = readTemp();
    float convertedTemp = convertRawTemp(rawTemp);

    return convertedTemp;
}

float SHT21::getRH()
{
    uint16_t rawRH = readRH();
    float convertedRH = convertRawRH(rawRH);

    return convertedRH;
}

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
	
	return -1;
}

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
	
	return -1;
}

float SHT21::convertRawTemp(uint16_t _rawTemp)
{
    float _temp = -46.85 + 175.72*((float)_rawTemp/(pow(2,16)));
    return _temp;
}

float SHT21::convertRawRH(uint16_t _rawRH)
{
    float _rh = -6 + 125*((float)_rawRH/(pow(2,16)));
    return _rh;
}

