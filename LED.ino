// กำหนดพอร์ตสำหรับ LED
const int LED_PIN = 9;  // ขา LED ต่อกับพอร์ต 9

void setup() {
  // กำหนดพอร์ตให้เป็น OUTPUT
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // เปิด LED
  digitalWrite(LED_PIN, HIGH);  // ตั้งค่าให้ LED ติด
  delay(1000);                  // หน่วงเวลา 1 วินาที (1000 มิลลิวินาที)

  // ปิด LED
  digitalWrite(LED_PIN, LOW);   // ตั้งค่าให้ LED ดับ
  delay(1000);                  // หน่วงเวลา 1 วินาที (1000 มิลลิวินาที)
}