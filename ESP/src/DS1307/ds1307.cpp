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

#include "si7034.h"
  
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

void DS1307::setupRealTime(NTCTime *NtcTime){
    _tm -> _secondes = NtcTime -> secondes;
    _tm -> _minutes = NtcTime -> minutes;
    _tm -> _hours = NtcTime -> hours;
    _tm -> _day = NtcTime -> day;
    _tm -> _date = NtcTime -> date;
    _tm -> _month = NtcTime -> month;
    _tm -> _year = NtcTime -> year;
}

RealTime DS1307::getRealTime(){
    return tm;
}

void SI7034::startMesurement()
{
    uint8_t addr[2];
    addr [0] = CMD1_MES_NH_NMODE;
    addr [1] = CMD2_MES_NH_NMODE;
    Wire.beginTransmission(SI7034_ADDR);
    Wire.write(addr, 2);
    Wire.endTransmission();

    delay(15);

    Wire.requestFrom(SI7034_ADDR, 6);

    if (6 <= Wire.available())
    {
        uint8_t _msbTemp = Wire.read();
        uint8_t _lsbTemp = Wire.read();
        uint8_t _checksumTemp = Wire.read();
        uint8_t _msbRH = Wire.read();
        uint8_t _lsbRH = Wire.read();
        uint8_t _checksumRH = Wire.read();

        uint16_t _rawTemp = ((_msbTemp << 8) | (_lsbTemp));
        uint16_t _rawRH = ((_msbRH << 8) | (_lsbRH));

        setRawTemp(_rawTemp);
        setRawRH(_rawRH);
    }

    setRawTemp(-1);
    setRawRH(-1);
}