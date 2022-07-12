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

// Librairie faite par nous-même pour utiliser les capteurs de la carte serveur
#include <sht21.h>
#include <bmp180.h>

// Déclaration des macros 
#define POWER_LEVEL 1
#define LORA_FREQUENCY 868000000

// Déclaration des constante
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;

// Déclaration des objets des classes
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

BMP180 bmp;
SHT21 sht;

// Déclaration des variables
float pressure, tmp, temp, rh;

// Déclaration des fonctions
void displayTemp(float temp);
void displayRh(float rh);
void displayPressure(float press);
void loraSendData(float temp, float rh, long press);
float getPowerLevel();


void setup() {
  // Initialisation des différents composants
  lcd.begin(16, 2);
  bmp.begin();
  sht.begin();
  Serial.begin(9600);

  // initialisation et configuration de Lora
  if (!LoRa.begin(LORA_FREQUENCY)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

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

  // Emission des données sur la carte serveur
  loraSendData(temp, rh, pressure);

  delay(500);
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
void loraSendData(float temp, float rh, long press)
{
  LoRa.beginPacket();
  LoRa.print(temp);
  LoRa.print(rh);
  LoRa.print(press);
  LoRa.endPacket();
}


