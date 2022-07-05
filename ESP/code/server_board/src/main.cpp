#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <WiFi.h>

#include <ds1307.h>
#include <si7034.h>


const char* ssid = "AjouterSSID"; // MODIFER !!
const char* password =  "AjouterMotDePasse"; // MODIFIER !!
const char* ntpServer = "time.google.com";

const int rs = 15, en = 2, d4 = 0, d5 = 4, d6 = 16, d7 = 17; 


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
DS1307 clk;
SI7034 sensor;


float temp = 0, rh = 0;
struct MyTime myTime;

void displayTimeDate(struct MyTime *time);
void displayTemp(float temp);
void displayRH(float rh);

void setup() {
  lcd.begin(16, 2);
  clk.begin();
  sensor.begin();
  WiFi.begin(ssid, password);
  Serial.begin(9600);

  Serial.println("Connected with success");
  configTime(0, 3600, ntpServer);

  struct tm rtm;

  if(getLocalTime(&rtm)){
    clk.setupRealTime(&rtm);
  }
}

void loop() {
  sensor.startMesurement();
  temp = sensor.getTemp();
  rh = sensor.getRH();
  clk.getRealTime(&myTime);

  displayTimeDate(&myTime);
  displayTemp(temp);
  displayRH(rh);

  delay(1000);
  lcd.clear();
}

void displayTimeDate(struct MyTime *time){
  lcd.setCursor(0, 0);
  lcd.print(time -> hours);
  lcd.setCursor(2, 0);
  lcd.print("h");
  lcd.setCursor(3, 0);
  lcd.print(time -> minutes);
  lcd.setCursor(5, 0);
  lcd.print("m");
  lcd.setCursor(6, 0);
  lcd.print(time -> secondes);
  lcd.setCursor(8, 0);
  lcd.print("s");

  lcd.setCursor(0, 1);
  lcd.print(time -> day);
  lcd.setCursor(2, 1);
  lcd.print("/");
  lcd.setCursor(3, 1);
  lcd.print(time -> month);
  lcd.setCursor(5, 1);
  lcd.print("/");
  lcd.setCursor(6, 1);
  lcd.print(time -> year);
}

void displayTemp(float temp){
  lcd.setCursor(10, 0);
  lcd.print(temp);
  lcd.setCursor(15, 0);
  lcd.print("C");
}

void displayRH(float rh){
  lcd.setCursor(10, 0);
  lcd.print(rh);
  lcd.setCursor(15, 0);
  lcd.print("%");
}
