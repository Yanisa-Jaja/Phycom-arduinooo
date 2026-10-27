void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);    // 4 = Trig
  pinMode(2, INPUT);     // 2 = Echo
}

void loop() {
  digitalWrite(4, HIGH);
  delayMicroseconds(10);
  digitalWrite(4, LOW);

  int pulseWidth = pulseIn(2, HIGH);

  Serial.print("Pulse Width: ");
  Serial.println(pulseWidth);

  long distance = pulseWidth / 29 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);

  delay(1000);
}
// VCC -> ต่อเข้าขา 5V
// GND -> ต่อเข้าขา GND
// Trig -> ต่อเข้าขา Digital Pin 4
// Echo -> ต่อเข้าขา Digital Pin 2//