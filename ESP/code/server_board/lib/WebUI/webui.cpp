/********************************************************
*                                                       *
*    PROJECT: WebUI for weather station                 *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 29/06/2022                                   *
*                                                       *
*********************************************************/


#include <Arduino.h>
#include <WiFiClient.h>
#include <WebServer.h>

#include "ds1307.h"
#include "webui.h"
#include "index.h"  

WebServer server(80);

void handleRoot();
void handleInTemp();
void handleInRh();
void handleOuTemp();
void handleOuRh();
void handlePress();
void handleDay();
void handleMonth();
void handleYear();
void handleHour();
void handleMin();
void handleSec();

float *inTemp, *inRh, *outTemp, *outRh;
int *day, *month, *year, *hours, *mins, *secs;
long  *outPress;

WEBUI::WEBUI()
{
}

void WEBUI::begin(){
    server.on("/", handleRoot);   
    server.on("/readIndoorTemp", handleInTemp);
    server.on("/readIndoorRh", handleInRh);
    server.on("/readOutdoorTemp", handleOuTemp);
    server.on("/readOutdoorRh", handleOuRh);
    server.on("/readPress", handlePress);

    server.on("/readDay", handleDay);
    server.on("/readMonth", handleMonth);
    server.on("/readYear", handleYear);
    server.on("/readHour", handleHour);
    server.on("/readMin", handleMin);
    server.on("/readSec", handleSec);

    server.begin();
}

void WEBUI::setValue(float *inT, float *inH, float *outT, float *outH, long *pressure, struct MyTime *myTm){
    inTemp = inT;
    inRh = inH;
    outTemp = outT;
    outRh = outH;
    outPress = pressure;
    day = &(myTm -> day);
    month = &(myTm -> month);
    year = &(myTm -> year);
    hours = &(myTm -> hours);
    mins = &(myTm -> minutes);
    secs= &(myTm -> secondes);
} 

void WEBUI::displayValue(){
    server.handleClient();
    delay(1);
}

void handleRoot() {
    String s = MAIN_page; 
    server.send(200, "text/html", s); 
}

void handleInTemp(){
    String Value = String(*inTemp);
    server.send(200, "text/plane", Value); 
}

void handleInRh(){
    String Value = String(*inRh);
    server.send(200, "text/plane", Value); 
}

void handleOuTemp(){
    String Value = String(*outTemp);
    server.send(200, "text/plane", Value); 
}

void handleOuRh(){
    String Value = String(*outRh);
    server.send(200, "text/plane", Value); 
}

void handlePress(){
    String Value = String(*outPress);
    server.send(200, "text/plane", Value); 
}

void handleDay(){
    String Value = String(*day);
    server.send(200, "text/plane", Value); 
}

void handleMonth(){
    String Value = String(*month);
    server.send(200, "text/plane", Value); 
}

void handleYear(){
    String Value = String(*year);
    server.send(200, "text/plane", Value); 
}

void handleHour(){
    String Value = String(*hours);
    server.send(200, "text/plane", Value); 
}

void handleMin(){
    String Value = String(*mins);
    server.send(200, "text/plane", Value); 
}

void handleSec(){
    String Value = String(*secs);
    server.send(200, "text/plane", Value); 
}
