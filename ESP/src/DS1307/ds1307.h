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
        void setupRealTime(RTime rtime);
        void getRealTime();
        
        struct RTime {
            int secondes = 0;
            int minutes = 0;
            int hours = 0;
            int day = 10;
            int date = 5;
            int month = 0;
            int year = 0;
        };

        RTime rtime;
       

    private:
        uint8_t decToBcd(uint8_t dec);
        uint8_t bcdToDec(uint8_t bcd);
};