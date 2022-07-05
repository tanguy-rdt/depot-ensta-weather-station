
/********************************************************
*                                                       *
*    PROJECT: SHT21 library for weather station         *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 29/06/2022                                   *
*                                                       *
*********************************************************/

class SHT21
{
    public:
     	SHT21();

        void begin();
        float getTemp();
        float getRH();

    private:
        uint16_t readTemp();
        uint16_t readRH();
	    float convertRawTemp(uint16_t rawTemp);
	    float convertRawRH(uint16_t rawRH);
};
