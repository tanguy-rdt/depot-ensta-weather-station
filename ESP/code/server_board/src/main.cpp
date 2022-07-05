#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <WiFi.h>

#include <ds1307.h>
#include <si7034.h>

const int rs = 15, en = 2, d4 = 0, d5 = 4, d6 = 16, d7 = 17; 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const char* ssid = "AjouterSSID";
const char* password =  "AjouterMotDePasse";

const char* ntpServer = "time.google.com";

DS1307 ds;
SI7034 si;

void setup() {
  lcd.begin(16, 2);
  ds.begin();
  si.begin();
  WiFi.begin(ssid, password);
  Serial.begin(9600);

  Serial.println("Connected with success");
  configTime(0, 3600, ntpServer);

  struct tm rtm;

  if(!getLocalTime(&rtm)){
    Serial.println("Unable to get real time, then setup the clock");
    return;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  float temp = si.getTemp();
  float rh = si.getRH();

  lcd.setCursor(0, 0);
  lcd.print(temp);
  lcd.setCursor(5, 0);
  lcd.print("C");
  
  lcd.setCursor(9, 0);
  lcd.print(rh);
  lcd.setCursor(14, 0);
  lcd.print("%");
  
  delay(500);
  lcd.clear();

}