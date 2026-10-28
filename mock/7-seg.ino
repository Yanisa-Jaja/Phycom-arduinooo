/*
 * Arduino UNO R4 WiFi - รับเลข 0-9 จาก MQTT แล้วแสดงบน 7-segment 1 หลัก
 * Topic: 68070032/prob_stat
 */

#include <WiFiS3.h>
#include <MQTTClient.h>

const char WIFI_SSID[] = "Java";
const char WIFI_PASSWORD[] = "29122549";

// ต้องเป็น broker เดียวกับที่ server ส่งค่ามา (ตรวจจากเอกสารแล็บ)
const char MQTT_BROKER_ADRRESS[] = "phycom.it.kmitl.ac.th";
const int MQTT_PORT = 1883;  // Arduino ใช้ TCP ธรรมดา
const char MQTT_CLIENT_ID[] = "jaja-7seg-68070032";
const char MQTT_USERNAME[] = "";
const char MQTT_PASSWORD[] = "";

const char SUBSCRIBE_TOPIC[] = "68070032/prob_stat";

// ---- วงจร 7-segment (แก้ให้ตรงกับที่ต่อจริง) ----
// ลำดับ: a, b, c, d, e, f, g
const int segPins[7] = {2, 3, 4, 5, 6, 7, 8};
const bool COMMON_ANODE = false;  // true = ขา common ต่อ 5V, false = ต่อ GND

// 1 = ส่วนนั้นติด (สำหรับ common cathode)
const byte digitPattern[10][7] = {
  {1, 1, 1, 1, 1, 1, 0},  // 0
  {0, 1, 1, 0, 0, 0, 0},  // 1
  {1, 1, 0, 1, 1, 0, 1},  // 2
  {1, 1, 1, 1, 0, 0, 1},  // 3
  {0, 1, 1, 0, 0, 1, 1},  // 4
  {1, 0, 1, 1, 0, 1, 1},  // 5
  {1, 0, 1, 1, 1, 1, 1},  // 6
  {1, 1, 1, 0, 0, 0, 0},  // 7
  {1, 1, 1, 1, 1, 1, 1},  // 8
  {1, 1, 1, 1, 0, 1, 1}   // 9
};

WiFiClient network;
MQTTClient mqtt = MQTTClient(256);

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }
  clearDisplay();

  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(WIFI_SSID);
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    delay(10000);
  }

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  mqtt.begin(MQTT_BROKER_ADRRESS, MQTT_PORT, network);
  mqtt.onMessage(messageReceived);
  connectToMQTT();
}

void loop() {
  mqtt.loop();

  if (!mqtt.connected()) {
    connectToMQTT();
  }
}

void connectToMQTT() {
  Serial.print("Connecting to MQTT broker");
  while (!mqtt.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();

  if (mqtt.subscribe(SUBSCRIBE_TOPIC))
    Serial.print("Subscribed to the topic: ");
  else
    Serial.print("Failed to subscribe to the topic: ");
  Serial.println(SUBSCRIBE_TOPIC);
}

void writeSegment(int index, bool on) {
  // common anode ต้องกลับขั้ว (LOW = ติด)
  digitalWrite(segPins[index], (on != COMMON_ANODE) ? HIGH : LOW);
}

void clearDisplay() {
  for (int i = 0; i < 7; i++) {
    writeSegment(i, false);
  }
}

void showDigit(int d) {
  for (int i = 0; i < 7; i++) {
    writeSegment(i, digitPattern[d][i] == 1);
  }
}

void messageReceived(String &topic, String &payload) {
  Serial.println("received from MQTT:");
  Serial.println("- topic: " + topic);
  Serial.println("- payload: " + payload);

  payload.trim();

  // รับเฉพาะตัวอักษรเดียวที่เป็น '0'-'9' (toInt ของข้อความอื่นจะได้ 0 ทำให้เข้าใจผิด)
  if (payload.length() == 1 && payload[0] >= '0' && payload[0] <= '9') {
    showDigit(payload[0] - '0');
  } else {
    Serial.println("Ignored: not a single digit 0-9");
  }
}
