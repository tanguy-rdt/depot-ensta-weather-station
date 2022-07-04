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
  
#define DS1307_ADDR               0xd0

#define SECONDES_ADDR             0x00
#define MINUTES_ADDR              0x01
#define HOURS_ADDR                0x02
#define DAY_ADDR                  0x03
#define DATE_ADDR                 0x04
#define MONTH_ADDR                0x05
#define YEAR_ADDR                 0x06



DS1307::DS1307()
{
}

void DS1307::setupRealTime(NTCTime *NtcTime)
{
    uint8_t addr[8];
    addr [0] = SECONDES_ADDR;
    addr [1] = decToBcd(NtcTime.secondes);
    addr [2] = decToBcd(NtcTime.minutes);
    addr [3] = decToBcd(NtcTime.hours);
    addr [4] = decToBcd(NtcTime.day);
    addr [5] = decToBcd(NtcTime.date);
    addr [6] = decToBcd(NtcTime.month);
    addr [7] = decToBcd(NtcTime.year);

    Wire.beginTransmission(SI7034_ADDR);
    Wire.write(addr, 8);
    Wire.endTransmission();
}

_RealTime DS1307::getRealTime()
{
    Wire.beginTransmission(SI7034_ADDR);
    Wire.write(SECONDES_ADDR);
    Wire.endTransmission();

    delay(15);

    Wire.requestFrom(SI7034_ADDR, 7);

    if (6 <= Wire.available())
    {
        _tm -> _secondes = bcdToDec(Wire.read() & 0x7f);
        _tm -> _minutes = bcdToDec(Wire.read());
        _tm -> _hours = bcdToDec(Wire.read() & 0x3f);
        _tm -> _day = bcdToDec(Wire.read());
        _tm -> _date = bcdToDec(Wire.read());
        _tm -> _month = bcdToDec(Wire.read());
        _tm -> _year = bcdToDec(Wire.read());

        return _tm;
    }

    return -1;
}

uint8_t DS1307::decToBcd(uint8_t dec)
{
    return ((dec/10 * 16) + (dec % 10));
}

uint8_t DS1307::bcdToDec(uint8_t bcd)
{
    return ((bcd/16 * 10) + (bcd % 16));
}