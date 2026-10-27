// กำหนดพอร์ตสำหรับ LED RGB
const int RED_PIN = 8;    // ขา Red
const int GREEN_PIN = 6;  // ขา Green
const int BLUE_PIN = 7;   // ขา Blue
//ขายาวเข้า 5V

// ฟังก์ชันช่วยเปิด/ปิดสี (RGB)
void setColor(bool red, bool green, bool blue) {
  digitalWrite(RED_PIN, red ? HIGH : LOW);
  digitalWrite(GREEN_PIN, green ? HIGH : LOW);
  digitalWrite(BLUE_PIN, blue ? HIGH : LOW);
}

void setup() {
  // กำหนดพอร์ตให้เป็น OUTPUT
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  // --- Mode 1: วน 7 สีหลัก (Rainbow Spectrum) ---
  setColor(HIGH, LOW,  LOW);  // สีแดง (Red)
  delay(500);
  setColor(LOW,  HIGH, LOW);  // สีเขียว (Green)
  delay(500);
  setColor(LOW,  LOW,  HIGH); // สีน้ำเงิน (Blue)
  delay(500);
  setColor(HIGH, HIGH, LOW);  // สีเหลือง (Yellow = Red + Green)
  delay(500);
  setColor(LOW,  HIGH, HIGH); // สีฟ้า (Cyan = Green + Blue)
  delay(500);
  setColor(HIGH, LOW,  HIGH); // สีชมพูม่วง (Magenta = Red + Blue)
  delay(500);
  setColor(HIGH, HIGH, HIGH); // สีขาว (White = RGB All On)
  delay(500);

  // --- Mode 2: ไฟไซเรนตำรวจ (Police Strobe) ---
  for (int i = 0; i < 8; i++) {
    setColor(HIGH, LOW, LOW); // แดง
    delay(80);
    setColor(LOW, LOW, HIGH); // น้ำเงิน
    delay(80);
  }

  // --- Mode 3: ดิสโก้สุ่มสี (Party Random Flash) ---
  for (int i = 0; i < 15; i++) {
    setColor(random(0, 2), random(0, 2), random(0, 2));
    delay(100);
  }

  // ปิดไฟพัก 0.5 วินาทีก่อนเริ่มรอบใหม่
  setColor(LOW, LOW, LOW);
  delay(500);
}