/********************************************************
*                                                       *
*    PROJECT: Si7034 library for weather station        *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 29/06/2022                                   *
*                                                       *
*********************************************************/


#include <Arduino.h>

class SI7034
{
    public:
        SI7034();

        void begin();
        void startMesurement();
        float getTemp();
        float getRH();

    private:
        uint16_t getRawTemp();
        uint16_t getRawRH();
        void setRawTemp(uint16_t rawTemp);
        void setRawRH(uint16_t rawRH);
        float convertRawTemp(uint16_t rawTemp);
        float convertRawRH(uint16_t rawRH);

        uint16_t _rawRH, _rawTemp;
};

