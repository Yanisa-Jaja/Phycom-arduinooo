// Keypad 4x4 test - ไม่ใช้ไลบรารี Keypad.h
// หลักการ: ตั้งแถว (row) เป็น OUTPUT แล้วสั่งทีละแถวให้เป็น LOW
//          อ่านคอลัมน์ (col) ที่เป็น INPUT_PULLUP ถ้าอ่านได้ LOW แปลว่าปุ่มตรงนั้นถูกกด

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// ขาที่ต่อกับ keypad (แก้ให้ตรงกับที่ต่อจริง)
const byte rowPins[ROWS] = {2, 3, 4, 5};  // R1, R2, R3, R4
const byte colPins[COLS] = {6, 7, 8, 9};  // C1, C2, C3, C4

char lastKey = 0;  // ปุ่มที่กดค้างอยู่ตอนนี้ (0 = ไม่มี)

// สแกน keypad คืนค่าปุ่มที่กด หรือ 0 ถ้าไม่มีปุ่มถูกกด
char scanKeypad() {
  for (byte r = 0; r < ROWS; r++) {
    digitalWrite(rowPins[r], LOW);          // เลือกแถวนี้

    for (byte c = 0; c < COLS; c++) {
      if (digitalRead(colPins[c]) == LOW) {  // เจอปุ่มถูกกด
        digitalWrite(rowPins[r], HIGH);      // คืนค่าแถวก่อนออก
        return keys[r][c];
      }
    }

    digitalWrite(rowPins[r], HIGH);         // เลิกเลือกแถวนี้
  }
  return 0;
}

void setup() {
  Serial.begin(9600);

  for (byte r = 0; r < ROWS; r++) {
    pinMode(rowPins[r], OUTPUT);
    digitalWrite(rowPins[r], HIGH);         // ปกติให้เป็น HIGH ไว้ก่อน
  }
  for (byte c = 0; c < COLS; c++) {
    pinMode(colPins[c], INPUT_PULLUP);
  }

  Serial.println("Keypad ready. Press any key...");
}

void loop() {
  char key = scanKeypad();

  // แสดงผลเฉพาะตอนเริ่มกดปุ่มใหม่ (ไม่พิมพ์ซ้ำตอนกดค้าง)
  if (key != 0 && key != lastKey) {
    Serial.print("Key pressed: ");
    Serial.println(key);
    delay(30);  // debounce กันสัญญาณเด้ง
  }

  lastKey = key;
}
