/********************************************************
*                                                       *
*    PROJECT: WebUI for weather station                 *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 29/06/2022                                   *
*                                                       *
*********************************************************/


#include <Arduino.h>

class WEBUI
{
    public:
        WEBUI();

        void begin();
        void displayValue();
        void setValue(float *inTemp, float *inRh, float *outTemp, float *outRh, long *Press, struct MyTime *myTm);
};


