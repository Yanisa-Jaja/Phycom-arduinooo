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

WiFiClient network;
MQTTClient mqtt = MQTTClient(256);

unsigned long lastPublishTime = 0;
const int potPin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);    // 4 = Trig
  pinMode(2, INPUT);     // 2 = Echo


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

String read() {
  digitalWrite(4, LOW);
  delayMicroseconds(2);
  digitalWrite(4, HIGH);
  delayMicroseconds(10);
  digitalWrite(4, LOW);

  long pulseWidth = pulseIn(2, HIGH, 30000);  // รอไม่เกิน 30 ms

  Serial.print("Pulse Width: ");
  Serial.println(pulseWidth);

  if (pulseWidth == 0) {          // ไม่มีเสียงสะท้อน
    Serial.println("No echo");
    return "off";                 // หรือจะเปลี่ยนเป็น "error" ก็ได้
  }

  long distanceCm = pulseWidth / 29 / 2;
  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  return (distanceCm > 20) ? "off" : "on";
}

void sendToMQTT() {
  String tempC = read(); // Fixed 'str' to 'String'
  char messageBuffer[16];
  tempC.toCharArray(messageBuffer, 16); 
  mqtt.publish(PUBLISH_TOPIC, messageBuffer);

  Serial.print("sent to ");
  Serial.print(PUBLISH_TOPIC);
  Serial.print(": ");
  Serial.println(messageBuffer);
}
