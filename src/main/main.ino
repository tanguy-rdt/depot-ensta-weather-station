#include <bmp180.h>
#include <LiquidCrystal.h>

#define RS 2
#define EN 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

LiquidCrystal lcd(RS, EN, D4, D5, D6, D6);
BMP180 bmp;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  bmp.begin();
}

void loop()
{
  long pressure = bmp.getPressure();
  lcd.print(pressure);
  delay(2000);
  lcd.clear();
}
