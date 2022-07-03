/********************************************************
*                                                       *
*    PROJECT: BMP180 library for weather station        *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 29/06/2022                                   *
*                                                       *
*********************************************************/


#include <Arduino.h>

class BMP180
{
    public:
        BMP180();

        int32_t getPressure();
        void begin();

        int32_t pressure;

    private:
        int32_t readPressure();
        int32_t convertRawPressure(int32_t rawPressure);
        int32_t read2SignedByte(int8_t addr);
        uint32_t read2UnsignedByte(int8_t addr);
        
        int16_t _ac1, _ac2, _ac3, _b1, _b2, _mb, _mc, _md, _oss;
        uint16_t _ac4, _ac5, _ac6;
        int32_t _x1, _x2, _x3, _b3, _b5, _b6, _b7 ;
        uint32_t _b4;
};
