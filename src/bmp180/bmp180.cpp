/********************************************************
*                                                       *
*    PROJECT: BMP180 library for weather station        *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 29/06/2022                                   *
*                                                       *
*********************************************************/


#include <Arduino.h>
#include <Wire.h>
#include <time.h>

#include "bmp180.h"
  
#define BMP180_ADDR           0x77
#define BMP180_CTRL_ADDR      0xf4

#define PRESS_CMD_ADDR        0x34

#define OUTPUT_MSB_ADDR       0xf6
#define OUTPUT_XLSB_ADDR      0xf8

#define ac1_MSB               0xaa
#define ac2_MSB               0xac
#define ac3_MSB               0xae
#define ac4_MSB               0xb0
#define ac5_MSB               0xb2
#define ac6_MSB               0xb4
#define b1_MSB                0xb6
#define b2_MSB                0xb8
#define mb_MSB                0xba
#define mc_MSB                0xbc
#define md_MSB                0xbe

BMP180::BMP180()
{
}

int32_t BMP180::getPressure()
{
    int32_t rawPressure = readPressure();
    int32_t convertedPressure = convertRawPressure(rawPressure);

    return convertedPressure;
}

void BMP180::begin()
{
    Wire.begin();
    _ac1 = read2SignedByte(ac1_MSB);
    _ac2 = read2SignedByte(ac2_MSB);
    _ac3 = read2SignedByte(ac3_MSB);
    _ac4 = read2UnsignedByte(ac4_MSB);
    _ac5 = read2UnsignedByte(ac5_MSB);
    _ac6 = read2UnsignedByte(ac6_MSB);
    _b1 = read2SignedByte(b1_MSB);
    _b2 = read2SignedByte(b2_MSB);
    _mb = read2SignedByte(mb_MSB);
    _mc = read2SignedByte(mc_MSB);
    _md = read2SignedByte(md_MSB);
    _oss = read2SignedByte(BMP180_CTRL_ADDR);
    _oss = (_oss & 0xc0) >> 6;
}

int32_t BMP180::readPressure()
{
    uint8_t addr[2];
    addr[0] = BMP180_CTRL_ADDR;
    addr[1] = PRESS_CMD_ADDR | (_oss << 6);
    Wire.beginTransmission(BMP180_ADDR);
    Wire.write(addr, 2);
    Wire.endTransmission();

    switch (_oss)
    {
    case 0:
        delay (4.5);
        break;

    case 1:
        delay (7.5);
        break;

    case 2:
        delay (13.5);
        break;

    case 3:
        delay (25.5);
        break;
    
    default:
        break;
    }


    Wire.beginTransmission(BMP180_ADDR);
    Wire.write(OUTPUT_MSB_ADDR);
    Wire.endTransmission();

    Wire.requestFrom(BMP180_ADDR, 2);


   if(Wire.available())
   {
        int8_t _msb = Wire.read();
        int8_t _lsb = Wire.read();
        //int8_t _xlsb = Wire.read(); // enable if oss > 0

        //int32_t pressure = ((_msb << 16) | (_lsb << 8) | (_xlsb)) >> (8 - _oss); // enable if oss > 0
	    int32_t pressure = ((_msb <<  8) | (_lsb)) ;

        return pressure;
    }

    return -1;
}


int32_t BMP180::convertRawPressure(int32_t up){ // add oss
    _b6 = _b5 - 4000;
    _x1 = (_b2 * (_b6 * _b6 / pow(2, 12))) / pow(2, 11);
    _x2 = _ac2 * _b6 / pow(2, 11);
    _x3 = _x1 + _x2;
    _b3 = ((_ac1 * 4 + _x3) << _oss + 2) / 4;
    _x1 = _ac3 * _b6 / pow(2, 13);
    _x2 = (_b1 * (_b6 * _b6 / pow(2, 12))) / pow(2, 16);
    _x3 = ((_x1 + _x2) + 2) / pow(2, 2);
    _b4 = _ac4 * (uint64_t)(_x3 + 32768) / pow(2, 15);
    _b7 = ((uint64_t)up - _b3) * (50000 >> _oss);
    if (_b7 < 0x80000000) 
    {
        pressure = (_b7 * 2) / _b4;
    }
    else
    {
        pressure = (_b7 / _b4) *2;
    }
    _x1 = (pressure / pow(2, 8)) * (pressure / pow(2, 8));
    _x1 = (_x1 * 3038) / pow(2, 16);
    _x2 = (-7357 * pressure) / pow(2, 16);
    pressure = pressure + (_x1 + _x2 + 3791) / pow(2, 4);

    return pressure;
}

int32_t BMP180::read2SignedByte(int8_t addr)
{
    Wire.beginTransmission(BMP180_ADDR);
    Wire.write(addr);
    Wire.endTransmission();

    Wire.requestFrom(BMP180_ADDR, 2);


    if (2 <= Wire.available())
    {
        int8_t _msb = Wire.read();
        int8_t _lsb = Wire.read();
        
        int32_t res = (_msb << 8) | _lsb;

        return res;
    }

    return 0;
}

uint32_t BMP180::read2UnsignedByte(int8_t addr)
{
    Wire.beginTransmission(BMP180_ADDR);
    Wire.write(addr);
    Wire.endTransmission();

    Wire.requestFrom(BMP180_ADDR, 2);


    if (2 <= Wire.available())
    {
        uint8_t _msb = Wire.read();
        uint8_t _lsb = Wire.read();
        
        uint32_t res = (_msb << 8) | _lsb;

        return res;
    }

    return 0;
}
