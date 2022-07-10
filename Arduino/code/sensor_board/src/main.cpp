/********************************************************
*                                                       *
*    PROJECT: main for weather station sensor board     *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 29/06/2022                                   *
*                                                       *
*********************************************************/


#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <LoRa.h>

#include <sht21.h>
#include <bmp180.h>

#define POWER_LEVEL 1
#define LORA_FREQUENCY 868000000

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

BMP180 bmp;
SHT21 sht;


float pressure, tmp, temp, rh;


void displayTemp(float temp);
void displayRh(float rh);
void displayPressure(float press);
void loraSendData(float temp, float rh, long press);
float getPowerLevel();


void setup() {
  lcd.begin(16, 2);
  bmp.begin();
  sht.begin();
  Serial.begin(9600);


  if (!LoRa.begin(LORA_FREQUENCY)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

}

void loop() {

  pressure = bmp.getPressure()/100;
  tmp = bmp.getTemp()/10;

  temp = sht.getTemp();
  rh = sht.getRH();

  displayTemp(temp);
  displayRh(rh);
  displayPressure(pressure);

  loraSendData(temp, rh, pressure);

  // normalement on doit pas l'afficher mais comme la pression du bmp marche pas ça me permet de debuger 
  // (la pression depend de la temp du bmp)
  lcd.setCursor(10, 1);
  lcd.print(tmp);

  delay(500);
  lcd.clear();
}

void displayTemp(float temp){
  lcd.setCursor(0, 0);
  lcd.print(temp);
  lcd.setCursor(5, 0);
  lcd.print("C");
}

void displayRh(float rh){
  lcd.setCursor(9, 0);
  lcd.print(rh);
  lcd.setCursor(14, 0);
  lcd.print("%");
}

void displayPressure(float press){
  lcd.setCursor(0, 1);
  lcd.print(press);
  lcd.setCursor(5, 1);
  lcd.print("hPa");
}

float getPowerLevel()
{
  return (3.3 * analogRead(POWER_LEVEL)) / 1023;
}

void loraSendData(float temp, float rh, long press)
{
  LoRa.beginPacket();
  LoRa.print(temp);
  LoRa.print(rh);
  LoRa.print(press);
  LoRa.endPacket();
}


