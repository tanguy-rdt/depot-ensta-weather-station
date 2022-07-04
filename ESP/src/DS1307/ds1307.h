/********************************************************
*                                                       *
*    PROJECT: DS1307 library for weather station        *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 29/06/2022                                   *
*                                                       *
*********************************************************/


#include <Arduino.h>

class DS1307
{
    public:
        DS1307();

        void begin();
        void setupRealTime(NTCTime *NtcTime);
        _RealTime getRealTime();
       

    private:
        struct _RealTime {
            _secondes;
            _minutes;
            _hours;
            _day;
            _date;
            _month;
            _year;
        };

        _RealTime _tm; 

        uint8_t decToBcd(uint8_t dec);
        uint8_t bcdToDec(uint8_t bcd);
};