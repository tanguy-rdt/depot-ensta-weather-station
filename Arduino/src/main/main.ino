#include <LiquidCrystal.h>
#include <Wire.h>
#include <sht21.h>
#include <bmp180.h>

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

BMP180 bmp;
SHT21 sht;

void setup() {
  lcd.begin(16, 2);
  bmp.begin();
  sht.begin();
  Serial.begin(9600);

  lcd.print("start");
  delay(2000);
  lcd.clear();

  Serial.print("hello");

}

void loop() {
  // put your main code here, to run repeatedly:

  float pressure = bmp.getPressure()/100;
  float tmp = bmp.getTemp()/10;

  float temp = sht.getTemp();
  float rh = sht.getRH();

  lcd.setCursor(0, 0);
  lcd.print(temp);
  lcd.setCursor(5, 0);
  lcd.print("C");
  
  lcd.setCursor(9, 0);
  lcd.print(rh);
  lcd.setCursor(14, 0);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print(pressure);

  lcd.setCursor(10, 1);
  lcd.print(tmp);

  
  delay(500);
  lcd.clear();

}
