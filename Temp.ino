// C++ code
#include <LiquidCrystal_I2C.h>
//
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int  temp = A0;

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
}

void loop()
{
  int val = analogRead(temp);
  float voltage = (val * 5.0) / 1023.0;
  float tempC = (voltage - 0.5) * 100.0;

  lcd.setCursor(6, 0);
  lcd.print(tempC, 2);
  lcd.print(" C  ");

  delay(500);
}