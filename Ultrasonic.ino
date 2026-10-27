int trigger = 5;
int echo = 4;

void setup() {
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  int pulseWidth = pulseIn(echo, HIGH);

  Serial.print("Pulse Width: ");
  Serial.println(pulseWidth);
  long distance = pulseWidth/29/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(1000);

}
