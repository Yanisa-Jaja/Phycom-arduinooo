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