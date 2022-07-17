/********************************************************
*                                                       *
*    PROJECT: main for weather station sensor board     *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 12/07/2022                                   *
*                                                       *
*********************************************************/

// Librairie de base de arduino
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <LoRa.h>
#include <SPI.h>

// Librairie faite par nous-même pour utiliser les capteurs de la carte serveur
#include <sht21.h>
#include <bmp180.h>

// Déclaration des macros 
#define POWER_LEVEL 1
//#define LORA_FREQUENCY 868E6

#define RS 2
#define EN 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

// Déclaration des objets des classes
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

BMP180 bmp;
SHT21 sht;

// Déclaration des variables
float pressure, tmp, temp, rh;

// Déclaration des fonctions
void displayTemp(float temp);
void displayRh(float rh);
void displayPressure(float press);
//void loraSendData(float temp, float rh, long press);
float getPowerLevel();


void setup() {
  // Initialisation des différents composants
  lcd.begin(16, 2);
  bmp.begin();
  sht.begin();
  Serial.begin(9600);

  // initialisation et configuration de Lora
  /*SPI.begin();
  LoRa.setPins();

  unsigned int myDelay = millis();

  int ret = 0;
  while ((myDelay + 10000) > millis()){
    ret = LoRa.begin(LORA_FREQUENCY);

    if (ret){
      Serial.println("Starting LoRa success!");
      LoRa.setSyncWord(0xa2);
      break;
    }
  }
  
  if (!ret){
    Serial.println("Starting LoRa failed!");
  }*/
}

void loop() {
  // Mesure des différentes données
  pressure = bmp.getPressure()/100;
  temp = sht.getTemp();
  rh = sht.getRH();

  // Affichage des différentes données sur l'écran
  displayTemp(temp);
  displayRh(rh);
  displayPressure(pressure);

  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(getPowerLevel());
  lcd.setCursor(5, 0);
  lcd.print("V");

  // Emission des données sur la carte serveur
  //loraSendData(temp, rh, pressure);

  delay(3000);
  lcd.clear();
}

// Fonction permettant l'affichage de la température sur l'écran
void displayTemp(float temp){
  lcd.setCursor(0, 0);
  lcd.print(temp);
  lcd.setCursor(5, 0);
  lcd.print("C");
}

// Fonction permettant l'affichage de l'humidité sur l'écran
void displayRh(float rh){
  lcd.setCursor(9, 0);
  lcd.print(rh);
  lcd.setCursor(14, 0);
  lcd.print("%");
}

// Fonction permettant l'affichage de la pression sur l'écran
void displayPressure(float press){
  lcd.setCursor(0, 1);
  lcd.print(press);
  lcd.setCursor(5, 1);
  lcd.print("hPa");
}

// Calcul du niveau d'allimentation 
float getPowerLevel()
{
  return (3.3 * analogRead(POWER_LEVEL)) / 1023;
}

// Fonction permettant l'émssion des données vers la carte serveur
/*void loraSendData(float temp, float rh, long press)
{
  LoRa.beginPacket();
  LoRa.print(temp);
  LoRa.print(rh);
  LoRa.print(press);
  LoRa.endPacket();
}*/


