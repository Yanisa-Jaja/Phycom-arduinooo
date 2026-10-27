const int buttonPin = 2;     // ขาสั้น (Cathode) -> ต่อผ่านตัวต้านทาน 220Ω แล้วเข้า GND
const int ledPin = 13;       // ขาข้างใดข้างหนึ่ง -> ต่อเข้า GND (ส่วนอีกข้างต่อเข้า Pin 2)

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // ตั้งค่าปุ่มกดเป็น INPUT_PULLUP (ปกติเป็น HIGH, พอกดจะเป็น LOW)
  pinMode(ledPin, OUTPUT);          // ตั้งค่าขา LED เป็น OUTPUT
}

void loop() {
  int buttonState = digitalRead(buttonPin); // อ่านค่าสถานะจากปุ่มกด

  // เมื่อกดปุ่ม สถานะจะกลายเป็น LOW
  if (buttonState == LOW) {
    digitalWrite(ledPin, HIGH); // สั่งให้ไฟ LED ติด
  } else {
    digitalWrite(ledPin, LOW);  // เมื่อปล่อยปุ่ม ให้ไฟ LED ดับ
  }
}