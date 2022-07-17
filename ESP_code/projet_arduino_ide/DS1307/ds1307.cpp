/********************************************************
*                                                       *
*    PROJECT: DS1307 library for weather station        *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 12/07/2022                                   *
*                                                       *
*********************************************************/

// Librairies de base à arduino
#include <Arduino.h>
#include <Wire.h>
#include <time.h>

// Déclaration du .h de la librairie
#include "ds1307.h"

// Déclaration des addr
#define DS1307_ADDR        0x68 // addr de l'esclave i2c
#define NVRAM_ADDR         0x00

// Déclaration des macros
#define HOUR_DEC           1


DS1307::DS1307() // Constructeur
{
    
}

DS1307::~DS1307() // Destructeur
{

}

void DS1307::begin()
{ // Initialisation du DS1307
    Wire.begin(); // Initialisation de la lib Wire
}

// Fonction permettant la configuration du temps sur le DS1307
void DS1307::setupRealTime(struct tm *time) 
{
    // La structure tm est déclaré dans la lib Time.h de arduino 
    uint8_t addr[8];

    /* On se place sur l'addresse 0x00 de la mémoire et ensuite on écris les valeurs à la suite.
    Les adresses s'incrèmente elle même donc il n'est pas nécessaire de dire à chaque fois dans qu'elle 
    adresse ont veut écrire.*/
    addr [0] = NVRAM_ADDR;
    addr [1] = decToBcd(time -> tm_sec);
    addr [2] = decToBcd(time -> tm_min);
    addr [3] = decToBcd(time -> tm_hour);
    addr [4] = decToBcd(time -> tm_wday);
    addr [5] = decToBcd(time -> tm_mday);
    addr [6] = decToBcd(time -> tm_mon);
    addr [7] = decToBcd(time -> tm_year);

    Wire.beginTransmission(DS1307_ADDR); // On démarre la transmission i2c
    /* on écris les 8 octets précédement décris où le premier octets correspont à l'adresse où écrire
    le premier octet*/
    Wire.write(addr, 8); 
    Wire.endTransmission();
}

// Fonction permttant la lecture du temps sur le DS1307
void DS1307::getRealTime(struct MyTime *myTm)
{
    Wire.beginTransmission(DS1307_ADDR);
    Wire.write(NVRAM_ADDR); // On se place à l'adresse 0x00 pour lire la première valeur
    Wire.endTransmission();

    delay(15);

    Wire.requestFrom(DS1307_ADDR, 7);

     if (7 <= Wire.available())
     {
        // Suite à la lecture des différentes valeurs ont les assignes directement dans une structure pour simplifier l'usage
        myTm -> secondes = bcdToDec(Wire.read() & 0x7f); // on prend compte le bit 8 qui n'est pas à lire
        myTm -> minutes = bcdToDec(Wire.read()); // on lit à l'adresse 0x01 ...
        myTm -> hours = bcdToDec(Wire.read() & 0x3f) + HOUR_DEC; // Ici on prend compte l'heure UTC+1
        myTm -> day = bcdToDec(Wire.read()); // on lit à l'adresse 0x03...
        myTm -> date = bcdToDec(Wire.read()); // ...
        myTm -> month = bcdToDec(Wire.read());
        myTm -> year = actualYear(bcdToDec(Wire.read())); // On oublie pas de convertir l'année, la valeur obtenu
                                                          // sont les années écoulées depuis 1900

        // On vérifie le bit 8 de l'adresse 0x00 s'il est à 1 c'est que le DS1307 n'est pas activé
        if (((myTm -> secondes) & 0x80) >> 7){
           Serial.print("DS1307 disable !");
        }
    }
}

// Permet la conversion à l'année actuel
int DS1307::actualYear(int yearsFrom1900)
{
    return 1900 + yearsFrom1900; // année 1900 + nombre d'année depuis 1900
}

// Permet la conversion de decimal à code binaire décimal utilsé par les registre du DS1307
uint8_t DS1307::decToBcd(uint8_t dec)
{
    return ((dec/10 * 16) + (dec % 10));
}

// Permet la conversion de code binaire décimal à décimal utilsé par les registre du DS1307
uint8_t DS1307::bcdToDec(uint8_t bcd)
{
    return ((bcd/16 * 10) + (bcd % 16));
}