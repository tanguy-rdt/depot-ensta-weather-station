/********************************************************
*                                                       *
*    PROJECT: main for weather station server board     *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 29/06/2022                                   *
*                                                       *
*********************************************************/


#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <WiFi.h>
#include <LoRa.h>


#include <ds1307.h>
#include <si7034.h>
#include <webui.h>
#include <index.h>

#define LORA_FREQUENCY 868000000


const char* ssid = "Livebox-3700"; // MODIFER !!
const char* password =  "AkqDmWVXX6vL2AxNxg"; // MODIFIER !!
const char* ntpServer = "time.google.com";

const int rs = 15, en = 2, d4 = 0, d5 = 4, d6 = 16, d7 = 17; 


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
DS1307 clk;
SI7034 sensor;
WEBUI webUI;


float inTemperature = 0, inHumidity = 0, outTemperature = 10, outHumidity = 90;
long outPressure = 1012;
struct MyTime myTime;

void displayTimeDate(struct MyTime *time);
void displayTemp(float temp);
void displayRH(float rh);
void loraGetData();


void setup() {
  lcd.begin(20, 4);
  clk.begin();
  sensor.begin();
  Serial.begin(9600);


  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password);
  while(WiFi.waitForConnectResult() != WL_CONNECTED){      
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  

  webUI.begin();

  configTime(0, 3600, ntpServer);


  if (!LoRa.begin(LORA_FREQUENCY)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  struct tm rtm;

  if(getLocalTime(&rtm)){
    clk.setupRealTime(&rtm);
    Serial.println(rtm.tm_hour);

  }
}

void loop() {
  inTemperature = sensor.getTemp();
  inHumidity = sensor.getRH();
  clk.getRealTime(&myTime);

  displayTimeDate(&myTime);    
  Serial.println(myTime.day);

  displayTemp(inTemperature);
  displayRH(inHumidity);

  loraGetData();

  webUI.setValue(&inTemperature, &inHumidity, &outTemperature, &outHumidity, &outPressure, &myTime);
  webUI.displayValue();

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
  lcd.print(time -> date);
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
  lcd.setCursor(0, 2);
  lcd.print(temp);
  lcd.setCursor(5, 2);
  lcd.print("C");
}

void displayRH(float rh){
  lcd.setCursor(0, 3);
  lcd.print(rh);
  lcd.setCursor(5, 3);
  lcd.print("%");
}

void loraGetData(){
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    while (LoRa.available()) {
      outTemperature = LoRa.read();
      outHumidity = LoRa.read();
      outPressure = LoRa.read();
    }
  }
}

