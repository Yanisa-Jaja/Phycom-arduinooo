#include <WiFiS3.h>
#include <MQTTClient.h>

const char WIFI_SSID[] = "Java";
const char WIFI_PASSWORD[] = "29122549";

const char MQTT_BROKER_ADRRESS[] = "phycom.it.kmitl.ac.th";
const int MQTT_PORT = 1883;  // Arduino ใช้ TCP ธรรมดา
const char MQTT_CLIENT_ID[] = "jaja-uno-68070032";
const char MQTT_USERNAME[] = "";
const char MQTT_PASSWORD[] = "";

const char PUBLISH_TOPIC[] = "68070032/food";
const int PUBLISH_INTERVAL = 5000;  // ส่งทุก 5 วินาที

// ---- พินแต่ละตัวต้องไม่ซ้ำกัน ----
const int TRIG_PIN   = 4;
const int ECHO_PIN   = 2;
const int BUTTON_PIN = 7;  // เดิมซ้ำกับ Echo (พิน 2) ย้ายมาใช้พิน 7

WiFiClient network;
MQTTClient mqtt = MQTTClient(256);

unsigned long lastPublishTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // กด = LOW

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
  connectToMQTT();
}

void loop() {
  mqtt.loop();

  if (!mqtt.connected()) {
    connectToMQTT();
  }

  if (millis() - lastPublishTime > PUBLISH_INTERVAL) {
    sendToMQTT();
    lastPublishTime = millis();
  }
}

void connectToMQTT() {
  Serial.print("Connecting to MQTT broker");
  while (!mqtt.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("MQTT broker Connected!");
}

// คืนระยะเป็นเซนติเมตร (0 = ไม่มีเสียงสะท้อน/อ่านไม่ได้)
long readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long pulseWidth = pulseIn(ECHO_PIN, HIGH, 30000);  // timeout 30 ms
  return pulseWidth / 29 / 2;
}

// คืนค่า "on" หรือ "off" ให้ครบทุกกรณี
String read() {
  bool pressed = (digitalRead(BUTTON_PIN) == LOW);
  long distanceCm = readDistanceCm();

  Serial.print("Button: ");
  Serial.print(pressed ? "pressed" : "released");
  Serial.print(" | Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  if (pressed && distanceCm >= 20) {
    return "on";
  }
  return "off";
}

void sendToMQTT() {
  String state = read();
  char messageBuffer[16];
  state.toCharArray(messageBuffer, 16);
  mqtt.publish(PUBLISH_TOPIC, messageBuffer);

  Serial.print("sent to ");
  Serial.print(PUBLISH_TOPIC);
  Serial.print(": ");
  Serial.println(messageBuffer);
}
