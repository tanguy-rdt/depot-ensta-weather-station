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

#define CMD1_MES_NH_NMODE         0x78
#define CMD2_MES_NH_NMODE         0x66

#define CMD1_MES_NH_FMODE         0x60
#define CMD2_MES_NH_FMODE         0x9c


SI7034::SI7034()
{
}

void SI7034::begin()
{
    Wire.begin();
}


float SI7034::getTemp()
{
    return convertRawRH(getRawTemp());
}

float SI7034::getRH()
{
    return convertRawRH(getRawRH());
}

uint16_t SI7034::getRawTemp()
{
    return _rawTemp;
}

uint16_t SI7034::getRawRH()
{
    return _rawRH;
}

void SI7034::setRawTemp(uint16_t rawTemp)
{   
    _rawTemp = rawTemp;
}

void SI7034::setRawRH(uint16_t rawRH)
{
    _rawRH = rawRH;
}

float SI7034::convertRawTemp(uint16_t rawTemp)
{
    return -45 + 175 * ((rawTemp)/pow(2, 16));
}

float SI7034::convertRawRH(uint16_t rawRH)
{
    return 100 * ((rawRH)/pow(2, 16));
}

void SI7034::startMesurement()
{
    uint8_t addr[2];
    addr [0] = CMD1_MES_NH_NMODE;
    addr [1] = CMD2_MES_NH_NMODE;
    Wire.beginTransmission(SI7034_ADDR);
    Wire.write(addr, 2);
    Wire.endTransmission();

    delay(100);

    Wire.requestFrom(SI7034_ADDR, 6);

    if (6 <= Wire.available())
    {
        uint8_t _msbTemp = Wire.read();
        uint8_t _lsbTemp = Wire.read();
        uint8_t _checksumTemp = Wire.read();
        uint8_t _msbRH = Wire.read();
        uint8_t _lsbRH = Wire.read();
        uint8_t _checksumRH = Wire.read();

        uint16_t _rawT = ((_msbTemp << 8) | (_lsbTemp));
        uint16_t _rawR = ((_msbRH << 8) | (_lsbRH));

        setRawTemp(_rawT);
        setRawRH(_rawR);

        return;
    }

    setRawTemp(-1);
    setRawRH(-1);
}