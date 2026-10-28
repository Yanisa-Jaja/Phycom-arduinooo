#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
//keypad 4x4 to LCD 16x2
// กำหนดขนาด Keypad (4 แถว 4 คอลัมน์)
const byte ROWS = 4;
const byte COLS = 4;

// แผนผังปุ่มกดของ Keypad 4x4
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// กำหนด พิน Digital บน Arduino ที่ต่อกับ Keypad
byte rowPins[ROWS] = {9, 8, 7, 6}; // แถว 1-4
byte colPins[COLS] = {5, 4, 3, 2}; // คอลัมน์ 1-4

// สร้างออบเจกต์สำหรับใช้งาน Keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// กำหนด Address I2C ของจอ LCD และขนาด 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

int cursorCol = 0; // ตำแหน่งคอลัมน์ตัวอักษรบนหน้าจอ LCD

void setup() {
  // เริ่มต้นการทำงานของจอ LCD
  lcd.init();
  lcd.backlight();
  
  // แสดงข้อความต้อนรับ
  lcd.setCursor(0, 0);
  lcd.print("Keypad to LCD");
  lcd.setCursor(0, 1);
  lcd.print("Press any key...");
  
  delay(2000);
  
  // ล้างหน้าจอเพื่อเตรียมรับค่า
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Input:");
}

void loop() {
  // อ่านค่าปุ่มที่ถูกกด
  char key = keypad.getKey();
  
  if (key) {
    // หากกดปุ่ม '*' จะเป็นการสั่ง Clear ล้างบรรทัดล่าง
    if (key == '*') {
      lcd.setCursor(0, 1);
      lcd.print("                "); // ลบข้อความแถวที่ 2
      cursorCol = 0;
    } 
    else {
      // แสดงค่าปุ่มกดที่บรรทัดด้านล่าง (บรรทัดที่ 1)
      lcd.setCursor(cursorCol, 1);
      lcd.print(key);
      
      cursorCol++;
      
      // ถ้ากดครบ 16 ตัวอักษร ให้รีเซ็ตกลับไปเริ่มคอลัมน์แรกใหม่
      if (cursorCol >= 16) {
        cursorCol = 0;
      }
    }
  }
}