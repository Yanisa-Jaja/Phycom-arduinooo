/*
 * Arduino UNO R4 WiFi - Experiment 6 (RGB LED control via MQTT)
 */

#include <WiFiS3.h>
#include <MQTTClient.h>
/*************************************************************************************************************** */
const char WIFI_SSID[] = "Java";
const char WIFI_PASSWORD[] = "29122549";

const char MQTT_BROKER_ADRRESS[] = "mqtt-dashboard.com";
// FIX: Arduino ใช้ WiFiClient (TCP ธรรมดา) ต้องใช้พอร์ต 1883
// พอร์ต 8884 เป็น WebSocket+TLS สำหรับเว็บเบราว์เซอร์เท่านั้น
const int MQTT_PORT = 1883;
const char MQTT_CLIENT_ID[] = "jaja-uno-r4-68070032";  // ห้ามซ้ำกับ client อื่น
const char MQTT_USERNAME[] = "";
const char MQTT_PASSWORD[] = "";

const char PUBLISH_TOPIC[] = "68070032/LEDSEND";    // Arduino -> ส่งออก
const char SUBSCRIBE_TOPIC[] = "68070032/LED";      // รับคำสั่งจากหน้าเว็บ (ตรงกับ HTML)

const int PUBLISH_INTERVAL = 5000;

WiFiClient network;
MQTTClient mqtt = MQTTClient(256);

unsigned long lastPublishTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);   // red
  pinMode(10, OUTPUT);  // green
  pinMode(11, OUTPUT);  // blue

  // FIX: common anode -> HIGH = ดับ ตั้งให้ดับตั้งแต่เริ่ม (เดิมไฟติดหมดจนกว่าจะมีคำสั่ง)
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);

  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    Serial.print("Arduino UNO R4 - Attempting to connect to SSID: ");
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

  // FIX: ถ้าหลุดจาก broker ให้ต่อใหม่อัตโนมัติ
  if (!mqtt.connected()) {
    connectToMQTT();
  }

  if (millis() - lastPublishTime > PUBLISH_INTERVAL) {
    sendToMQTT();
    lastPublishTime = millis();
  }
}

void connectToMQTT() {
  Serial.print("Arduino UNO R4 - Connecting to MQTT broker");

  while (!mqtt.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();

  if (mqtt.subscribe(SUBSCRIBE_TOPIC))
    Serial.print("Arduino UNO R4 - Subscribed to the topic: ");
  else
    Serial.print("Arduino UNO R4 - Failed to subscribe to the topic: ");

  Serial.println(SUBSCRIBE_TOPIC);
  Serial.println("Arduino UNO R4 - MQTT broker Connected!");
}

void sendToMQTT() {
  int val = millis() / 1000;
  String val_str = String(val);
  char messageBuffer[10];
  val_str.toCharArray(messageBuffer, 10);
  mqtt.publish(PUBLISH_TOPIC, messageBuffer);

  Serial.println("Arduino UNO R4 - sent to MQTT:");
  Serial.print("- topic: ");
  Serial.println(PUBLISH_TOPIC);
  Serial.print("- payload: ");
  Serial.println(messageBuffer);
}

void messageReceived(String &topic, String &payload) {
  Serial.println("Arduino UNO R4 - received from MQTT:");
  Serial.println("- topic: " + topic);
  Serial.println("- payload: " + payload);

  // payload จากเว็บ: {"r":1,"g":0,"b":1}
  int rIndex = payload.indexOf("\"r\":");
  int gIndex = payload.indexOf("\"g\":");
  int bIndex = payload.indexOf("\"b\":");

  if (rIndex >= 0 && gIndex >= 0 && bIndex >= 0) {
    int rVal = payload.substring(rIndex + 4, rIndex + 5).toInt();
    int gVal = payload.substring(gIndex + 4, gIndex + 5).toInt();
    int bVal = payload.substring(bIndex + 4, bIndex + 5).toInt();

    // common anode: 1 (ON) = LOW, 0 (OFF) = HIGH
    digitalWrite(9,  rVal == 1 ? LOW : HIGH);   // RED
    digitalWrite(10, gVal == 1 ? LOW : HIGH);   // GREEN
    digitalWrite(11, bVal == 1 ? LOW : HIGH);   // BLUE
  }
}
