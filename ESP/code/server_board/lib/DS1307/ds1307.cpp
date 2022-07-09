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
  
#define DS1307_ADDR        0x68
#define NVRAM_ADDR         0x00
#define HOUR_DEC           1


DS1307::DS1307()
{
    
}

DS1307::~DS1307()
{

}

void DS1307::begin(){
    Wire.begin();
}

 void DS1307::setupRealTime(struct tm *time)
 {
     uint8_t addr[8];
     addr [0] = NVRAM_ADDR;
     addr [1] = decToBcd(time -> tm_sec);
     addr [2] = decToBcd(time -> tm_min);
     addr [3] = decToBcd(time -> tm_hour);
     addr [4] = decToBcd(time -> tm_wday);
     addr [5] = decToBcd(time -> tm_mday);
     addr [6] = decToBcd(time -> tm_mon);
     addr [7] = decToBcd(time -> tm_year);

     Wire.beginTransmission(DS1307_ADDR);
     Wire.write(addr, 8);
     Wire.endTransmission();
 }

void DS1307::getRealTime(struct MyTime *myTm)
{
     Wire.beginTransmission(DS1307_ADDR);
     Wire.write(NVRAM_ADDR);
     Wire.endTransmission();

     delay(15);

     Wire.requestFrom(DS1307_ADDR, 7);

     if (7 <= Wire.available())
     {
         myTm -> secondes = bcdToDec(Wire.read() & 0x7f);
         myTm -> minutes = bcdToDec(Wire.read());
         myTm -> hours = bcdToDec(Wire.read() & 0x3f) + HOUR_DEC;
         myTm -> day = bcdToDec(Wire.read());
         myTm -> date = bcdToDec(Wire.read());
         myTm -> month = bcdToDec(Wire.read());
         myTm -> year = actualYear(bcdToDec(Wire.read()));

         if (((myTm -> secondes) & 0x80) >> 7){
            Serial.print("DS1307 disable !");
         }
     }
 }

 int DS1307::actualYear(int yearsFrom1900){
    return 1900 + yearsFrom1900;
 }

 uint8_t DS1307::decToBcd(uint8_t dec)
 {
     return ((dec/10 * 16) + (dec % 10));
 }

 uint8_t DS1307::bcdToDec(uint8_t bcd)
 {
     return ((bcd/16 * 10) + (bcd % 16));
 }