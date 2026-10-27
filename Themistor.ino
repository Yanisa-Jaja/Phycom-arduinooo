int voltage = A0;

void setup() {
  Serial.begin(9600);
  pinMode(voltage, INPUT);
}

void loop() {
  int rawVal = analogRead(voltage);
if (rawVal >= 1023) rawVal = 1022;

  float R_fixed = 10000.0;
  
  float R_th = R_fixed * ((float)rawVal / (1023.0 - rawVal));

  float beta = 3950.0;     // ค่า Beta ของ Thermistor
  float r0 = 10000.0;      // ค่า R ที่ 25 C
  float t0 = 298.15;       // 25 C ในหน่วย Kelvin

  float tempK = 1.0 / ((1.0 / t0) + (1.0 / beta) * log(R_th / r0));
  float tempC = tempK - 273.15;
  Serial.print(tempC);
  Serial.println(" C");
}
