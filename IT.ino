#include <LiquidCrystal_I2C.h>
//
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int  temp = A0;

byte heart[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

byte degree[8] = {
  B11100,
  B10100,
  B11100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup()
{
  lcd.init();
  lcd.backlight();

  lcd.createChar(0, heart);
  lcd.createChar(1, degree);

  lcd.setCursor(5, 0);
  lcd.print("I ");
  lcd.write(byte(0));
  lcd.print(" IT");
}

void loop()
{
  int val = analogRead(temp);
  float voltage = (val * 5.0) / 1023.0;
  float tempC = (voltage - 0.5) * 100.0;

  lcd.setCursor(0, 1);
  lcd.print("68070032 ");
  lcd.print(tempC, 2);
  lcd.write(byte(1));
  lcd.print("C");

  delay(500);
}