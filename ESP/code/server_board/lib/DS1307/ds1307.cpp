/********************************************************
*                                                       *
*    PROJECT: DS1307 library for weather station        *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 29/06/2022                                   *
*                                                       *
*********************************************************/


#include <Arduino.h>
#include <Wire.h>
#include <time.h>

#include "ds1307.h"
  
#define DS1307_ADDR               0x68

#define NVRAM_ADDR                0x00


DS1307::DS1307()
{
    Wire.begin();
}

 void DS1307::setupRealTime(RTime rtime)
 {
     uint8_t addr[8];
     addr [0] = NVRAM_ADDR;
     addr [1] = decToBcd(rtime.secondes);
     addr [2] = decToBcd(rtime.minutes);
     addr [3] = decToBcd(rtime.hours);
     addr [4] = decToBcd(rtime.day);
     addr [5] = decToBcd(rtime.date);
     addr [6] = decToBcd(rtime.month);
     addr [7] = decToBcd(rtime.year);

     Wire.beginTransmission(DS1307_ADDR);
     Wire.write(addr, 8);
     Wire.endTransmission();
 }

 void DS1307::getRealTime()
 {
     Wire.beginTransmission(DS1307_ADDR);
     Wire.write(NVRAM_ADDR);
     Wire.endTransmission();

     delay(15);

     Wire.requestFrom(DS1307_ADDR, 7);

     if (7 <= Wire.available())
     {
         rtime.secondes = bcdToDec(Wire.read());
         rtime.minutes = bcdToDec(Wire.read());
         rtime.hours = bcdToDec(Wire.read() & 0x3f);
         rtime.day = bcdToDec(Wire.read());
         rtime.date = bcdToDec(Wire.read());
         rtime.month = bcdToDec(Wire.read());
         rtime.year = bcdToDec(Wire.read());
     }
 }

 uint8_t DS1307::decToBcd(uint8_t dec)
 {
     return ((dec/10 * 16) + (dec % 10));
 }

 uint8_t DS1307::bcdToDec(uint8_t bcd)
 {
     return ((bcd/16 * 10) + (bcd % 16));
 }