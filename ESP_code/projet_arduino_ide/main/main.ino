/********************************************************
*                                                       *
*    PROJECT: main for weather station server board     *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 12/07/2022                                   *
*                                                       *
*********************************************************/


// Librairie arduino de base
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <WiFi.h>
#include <LoRa.h>


// Librairie faite par nous-même pour utiliser les capteurs de la carte serveur
#include <ds1307.h>
#include <si7034.h>
#include <webui.h>
#include <index.h>

// Déclaration des macros 
/*#define LORA_FREQUENCY 868E6

#define RESET 14
#define DIO0 26
#define SS 18
#define SCK 5
#define MISO 19
#define MOSI 27*/

#define RS 15
#define EN 2
#define D4 0
#define D5 4
#define D6 16
#define D7 17


// Déclaration des constante
const char* ssid = ""; // MODIFER !!
const char* password =  ""; // MODIFIER !!
const char* ntpServer = "time.google.com";

// Déclaration des objets des classes
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

DS1307 clk;
SI7034 sensor;
WEBUI webUI;

// Déclaration des variables
float inTemperature = 0, inHumidity = 0, outTemperature = 10, outHumidity = 90;
long outPressure = 1012;
struct MyTime myTime;

// Déclaration des fonctions
void displayTimeDate(struct MyTime *time);
void displayTemp(float temp);
void displayRH(float rh);
//void loraGetData();


void setup() {
  // Initialisation des différents composants
  lcd.begin(20, 4);
  clk.begin();
  sensor.begin();
  Serial.begin(9600);

  // Initialisation et configuration du wifi
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

  // Initialisation de l'interface web
  webUI.begin();

  configTime(0, 3600, ntpServer); // configuration du temps réel sur l'esp
                                  // depuis le serveur ntp

                                    // Obtention du temps réel et configuration dans le DS1307
  struct tm rtm;

  if(getLocalTime(&rtm)){
    clk.setupRealTime(&rtm);
    Serial.println(rtm.tm_hour);

  }

  // initialisation et configuration de Lora
  /*SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RESET, DIO0);    

  int myDelay = millis();

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
  inTemperature = sensor.getTemp();
  inHumidity = sensor.getRH();
  clk.getRealTime(&myTime);

  // Réception des données de la carte capteur
  //loraGetData();

  // Affichage des différentes données sur l'écran
  displayTimeDate(&myTime);    
  displayTemp(inTemperature);
  displayRH(inHumidity);

  // Affichage des différentes données sur l'interface web
  webUI.setValue(&inTemperature, &inHumidity, &outTemperature, &outHumidity, &outPressure, &myTime);
  webUI.displayValue();

  delay(1000);
  lcd.clear();
}

// Fonction permettant l'affichage du temps réel sur l'écran
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

// Fonction permettant l'affichage de la température sur l'écran
void displayTemp(float temp){
  lcd.setCursor(0, 2);
  lcd.print(temp);
  lcd.setCursor(5, 2);
  lcd.print("C");
}

// Fonction permettant l'affichage de l'humidité sur l'écran
void displayRH(float rh){
  lcd.setCursor(0, 3);
  lcd.print(rh);
  lcd.setCursor(5, 3);
  lcd.print("%");
}

// Fonction permettant la réception des données de la carte capteur
/*void loraGetData(){
  int packetSize = LoRa.parsePacket();

  // Si des paquets sont à lire alors on les lis
  if (packetSize) {
    while (LoRa.available()) {
      outTemperature = LoRa.read();
      outHumidity = LoRa.read();
      outPressure = LoRa.read();
    }
  }
}*/

