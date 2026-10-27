#include <math.h>

const int THERMISTOR_PIN = A0;

const float V_IN = 5.0;
const float R_FIXED = 10000.0;

const float NOMINAL_RESISTANCE = 10000.0;
const float NOMINAL_TEMP = 25.0;
const float B_COEFFICIENT = 3950.0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int rawThermistor = analogRead(THERMISTOR_PIN);
  float vOutThermistor = rawThermistor * (V_IN / 1023.0);

  // แก้ไขสูตรคำนวณค่าความต้านทาน Thermistor
  float rThermistor = R_FIXED * (vOutThermistor / (V_IN - vOutThermistor));

  float steinhart;
  steinhart = rThermistor / NOMINAL_RESISTANCE;
  steinhart = log(steinhart);
  steinhart /= B_COEFFICIENT;
  steinhart += 1.0 / (NOMINAL_TEMP + 273.15);
  steinhart = 1.0 / steinhart;
  float tempThermistor = steinhart - 273.15;

  Serial.print("Thermistor Temp: ");
  Serial.print(tempThermistor, 2);
  Serial.println(" °C");

  delay(1000);
}