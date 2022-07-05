/********************************************************
*                                                       *
*    PROJECT: DS1307 library for weather station        *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 29/06/2022                                   *
*                                                       *
*********************************************************/


#include <Arduino.h>

struct MyTime {
    int secondes;
    int minutes;
    int hours;
    int day;
    int date;
    int month;
    int year;
};       

class DS1307
{
    public:
        DS1307();
        ~DS1307();

        void begin();
        void setupRealTime(struct tm *time);
        void getRealTime(struct MyTime *myTm);
        

    private:
        uint8_t decToBcd(uint8_t dec);
        uint8_t bcdToDec(uint8_t bcd);
};