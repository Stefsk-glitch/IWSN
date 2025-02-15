#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

const char* ssid = "xxx";
const char* password = "xxx";

const char* mqtt_broker = "xxx";
const int mqtt_port = 8883;
const char* mqtt_username = "xxx";
const char* mqtt_password = "xxx";

const char* topic = "/test";

WiFiClientSecure wifiClient;
PubSubClient mqttClient(wifiClient);

long previous_time = 0;

void setupMQTT() 
{
  mqttClient.setServer(mqtt_broker, mqtt_port);
}

void reconnect() 
{
  Serial.println("Connecting to MQTT Broker...");
  
  while (!mqttClient.connected()) 
  {
    Serial.println("Reconnecting to MQTT Broker...");
    String clientId = "123";
    
    if (mqttClient.connect(clientId.c_str(), mqtt_username, mqtt_password)) 
    {
      Serial.println("Connected to MQTT Broker.");
    } 

    else 
    {
      Serial.print("Failed");
      Serial.print(mqttClient.state());
      Serial.println(" Trying again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() 
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected to Wi-Fi");

  wifiClient.setInsecure();
  setupMQTT();
}

void loop() 
{
  if (!mqttClient.connected()) 
  {
    reconnect();
  }
  mqttClient.loop();

  // Publish every 60 seconds
  long now = millis();
  if (now - previous_time > 6000) 
  { 
    previous_time = now;
    
    mqttClient.publish(topic, "test");
  }
}