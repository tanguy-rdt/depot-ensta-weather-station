/********************************************************
*                                                       *
*    PROJECT: WebUI for weather station                 *
*    ORGANIZATION: ENSTA Bretagne FIPASE 2024           *
*    AUTEUR: Tanguy ROUDAUT, Tom ALLAIN                 *
*    DATE: 12/07/2022                                   *
*                                                       *
*********************************************************/

// Librairies de base à arduino
#include <Arduino.h>
#include <WiFiClient.h>
#include <WebServer.h>

// Déclaration du .h de la librairie et des lib perso utilisé dans le webui.cpp
#include "ds1307.h"
#include "webui.h"
#include "index.h"  // site html

// Déclaration de l'objet de la classe WebServer inclus à WebServer.h
WebServer server(80);

// Déclaration des fonctions
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

// Déclaration des fonction globals
float *inTemp, *inRh, *outTemp, *outRh;
int *date, *month, *year, *hours, *mins, *secs;
long  *outPress;

WEBUI::WEBUI() // Constructeur
{
}

WEBUI::~WEBUI() // Destructeur
{
}

void WEBUI::begin() // initialisation 
{
    server.on("/", handleRoot); // evenement pour charger la page html
    server.on("/readIndoorTemp", handleInTemp); // evenement pour charger la temp intérieur
    server.on("/readIndoorRh", handleInRh); // evenement pour charger l'humidité interieur
    server.on("/readOutdoorTemp", handleOuTemp);
    server.on("/readOutdoorRh", handleOuRh);
    server.on("/readPress", handlePress);

    server.on("/readDay", handleDay);
    server.on("/readMonth", handleMonth);
    server.on("/readYear", handleYear);
    server.on("/readHour", handleHour);
    server.on("/readMin", handleMin);
    server.on("/readSec", handleSec);

    server.begin(); // Démarrage du serveur
}

// Fonction permettant de configurer les valeurs à afficher sur l'interface graphique
void WEBUI::setValue(float *inT, float *inH, float *outT, float *outH, long *pressure, struct MyTime *myTm) 
{
    inTemp = inT;
    inRh = inH;
    outTemp = outT;
    outRh = outH;
    outPress = pressure;
    date = &(myTm -> date);
    month = &(myTm -> month);
    year = &(myTm -> year);
    hours = &(myTm -> hours);
    mins = &(myTm -> minutes);
    secs= &(myTm -> secondes);
} 

// Fonction pour afficher les valeurs
void WEBUI::displayValue()
{
    server.handleClient();
    delay(1);
}

// Permet de charger la page html
void handleRoot() 
{
    String s = MAIN_page; // récupère la page html sous forme de string qui est dans index.h
    server.send(200, "text/html", s); // envoie une requette d'écriture au serveur web
}

// Permet de charger la température intérieur
void handleInTemp()
{
    String Value = String(*inTemp); // récupère sous forme de string la temp
    server.send(200, "text/plane", Value); // envoie une requette d'écriture au serveur web
}

// Permet de charger l'humidité interieur
void handleInRh()
{
    String Value = String(*inRh);
    server.send(200, "text/plane", Value); 
}

void handleOuTemp()
{
    String Value = String(*outTemp);
    server.send(200, "text/plane", Value); 
}

void handleOuRh()
{
    String Value = String(*outRh);
    server.send(200, "text/plane", Value); 
}

void handlePress()
{
    String Value = String(*outPress);
    server.send(200, "text/plane", Value); 
}

void handleDay()
{
    String Value = String(*date);
    server.send(200, "text/plane", Value); 
}

void handleMonth()
{
    String Value = String(*month);
    server.send(200, "text/plane", Value); 
}

void handleYear()
{
    String Value = String(*year);
    server.send(200, "text/plane", Value); 
}

void handleHour()
{
    String Value = String(*hours);
    server.send(200, "text/plane", Value); 
}

void handleMin()
{
    String Value = String(*mins);
    server.send(200, "text/plane", Value); 
}

void handleSec()
{
    String Value = String(*secs);
    server.send(200, "text/plane", Value); 
}
