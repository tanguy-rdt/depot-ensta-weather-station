#include <LiquidCrystal.h>
#include <Wire.h>
//#include <ds1307.h>
#include <si7034.h>

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//DS1307 ds;
SI7034 si;

void setup() {
  lcd.begin(16, 2);
  //ds.begin();
  si.begin();
  Serial.begin(9600);

  lcd.print("start");
  delay(2000);
  lcd.clear();

  Serial.print("hello");

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


//  #include <WiFi.h>

 
// const char* ntpServer = "time.google.com";
 
// void printTime(){
  
//   struct tm time;
   
//   if(!getLocalTime(&time)){
//     Serial.println("Could not obtain time info");
//     return;
//   }
 
//   Serial.println("\n---------TIME----------");
   
//   Serial.print("Number of years since 1900: ");
//   Serial.println(time.tm_year);
 
//   Serial.print("month, from 0 to 11: ");
//   Serial.println(time.tm_mon);
 
//   Serial.print("day, from 1 to 31: "); 
//   Serial.println(time.tm_mday);
 
//   Serial.print("hour, from 0 to 23: ");
//   Serial.println(time.tm_hour);
 
//   Serial.print("minute, from 0 to 59: ");
//   Serial.println(time.tm_min);
   
//   Serial.print("second, from 0 to 59: ");
//   Serial.println(time.tm_sec);
// }
 
// void setup()
// {
//   Serial.begin(115200);
   
//   WiFi.begin();
   
//   Serial.println("Connected with success");
   
//   configTime(0, 3600, ntpServer);
// }
 
// void loop()
// {
//   printTime();
//   delay(5000);
// }