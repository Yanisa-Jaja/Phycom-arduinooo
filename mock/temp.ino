#include <WiFiS3.h>
#include <MQTTClient.h>
/*************************************************************************************************************** */
const char WIFI_SSID[] = "Java";
const char WIFI_PASSWORD[] = "29122549";

const char MQTT_BROKER_ADRRESS[] = "mqtt-dashboard.com";
// FIX: Arduino ใช้ WiFiClient (TCP ธรรมดา) ต้องใช้พอร์ต 1883
// พอร์ต 8884 เป็น WebSocket+TLS สำหรับเว็บเบราว์เซอร์เท่านั้น
const int MQTT_PORT = 1883;
const char MQTT_CLIENT_ID[] = "jaja-uno-68070032";  // ห้ามซ้ำกับ client อื่น
const char MQTT_USERNAME[] = "";
const char MQTT_PASSWORD[] = "";

const char PUBLISH_TOPIC[] = "68070032/temp";    // Arduino -> ส่งออก
const char SUBSCRIBE_TOPIC[] = "68070032/temp";      // รับคำสั่งจากหน้าเว็บ (ตรงกับ HTML)

const int PUBLISH_INTERVAL = 5000;

WiFiClient network;
MQTTClient mqtt = MQTTClient(256);

unsigned long lastPublishTime = 0;

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
}
