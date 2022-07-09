/********************************************************
*                                                       *
*    PROJECT: Si7034 library for weather station        *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 29/06/2022                                   *
*                                                       *
*********************************************************/


#include <Arduino.h>
#include <Wire.h>
#include <time.h>

#include "si7034.h"
  
#define SI7034_ADDR               0x70

#define TEMP_MES_NH_NMODE         0x78
#define RH_MES_NH_NMODE           0x66


SI7034::SI7034()
{
}

void SI7034::begin()
{
    Wire.begin();
}


float SI7034::getTemp()
{
    uint16_t rawTemp = readRawTemp();
    float temp = convertRawTemp(rawTemp);

    return temp;
}

float SI7034::getRH()
{
    uint16_t rawRh = readRawRh();
    float rh = convertRawTemp(rawRh);

    return rh;
}

uint16_t SI7034::readRawTemp(){
    Wire.beginTransmission(SI7034_ADDR);
    Wire.write(TEMP_MES_NH_NMODE);
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


uint16_t SI7034::readRawRh(){
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

float SI7034::convertRawTemp(uint16_t rawTemp)
{
    return -45 + 175 * ((rawTemp)/pow(2, 16));
}

float SI7034::convertRawRH(uint16_t rawRH)
{
    return 100 * ((rawRH)/pow(2, 16));
}