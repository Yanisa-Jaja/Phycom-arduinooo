/*
 * Arduino UNO R4 WiFi - รับค่าตัวเลขจาก MQTT แล้วเปิด LED ตามช่วง
 *   10 - 25  -> led3 (พิน 5)
 *   26 - 35  -> led2 (พิน 4)
 *   36 - 50  -> led1 (พิน 3)
 *   นอกช่วง   -> ดับทั้งหมด
 */

#include <WiFiS3.h>
#include <MQTTClient.h>

const char WIFI_SSID[] = "Java";
const char WIFI_PASSWORD[] = "29122549";

const char MQTT_BROKER_ADRRESS[] = "phycom.it.kmitl.ac.th";  // ต้องเป็น broker เดียวกับฝั่งที่ส่งค่า
const int MQTT_PORT = 1883;  // Arduino ใช้ TCP ธรรมดา
const char MQTT_CLIENT_ID[] = "jaja-uno-r4-68070032";
const char MQTT_USERNAME[] = "";
const char MQTT_PASSWORD[] = "";

const char SUBSCRIBE_TOPIC[] = "68070032/venus";

WiFiClient network;
MQTTClient mqtt = MQTTClient(256);

const int led1 = 3;
const int led2 = 4;
const int led3 = 5;

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  setLeds(LOW, LOW, LOW);  // เริ่มต้นดับทั้งหมด

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

void setLeds(int s1, int s2, int s3) {
  digitalWrite(led1, s1);
  digitalWrite(led2, s2);
  digitalWrite(led3, s3);
}

void messageReceived(String &topic, String &payload) {
  Serial.println("received from MQTT:");
  Serial.println("- topic: " + topic);
  Serial.println("- payload: " + payload);

  float value = payload.toFloat();  // แปลงข้อความเป็นตัวเลข เช่น "27.4" -> 27.4

  if (value >= 10 && value <= 25) {
    setLeds(LOW, LOW, HIGH);        // led3
  } else if (value > 25 && value <= 35) {
    setLeds(LOW, HIGH, LOW);        // led2
  } else if (value > 35 && value <= 50) {
    setLeds(HIGH, LOW, LOW);        // led1
  } else {
    setLeds(LOW, LOW, LOW);         // นอกช่วง ดับทั้งหมด
  }
}
