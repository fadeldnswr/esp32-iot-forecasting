#include <Arduino.h>
#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Define sensor type and pin
#define DHTTYPE DHT22
int sensorPin = 18;

// WiFi configuration
const char* ssid = "odoxs";
const char* password = "kingking04";
const char* mqttServer = "Raspberry Pi Ip"; // Change into Raspberry Pi IP

// Define struct configuration
WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(sensorPin, DHTTYPE);

// Define global variable for metrics measurement
unsigned long lastMillis = 0; // Last time data was sent
unsigned long latency = 0; // Store latency data
unsigned long throughput = 0; // Store throughput
float powerConsumption = 0.0; // Power consumption in mA

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("DHT22 Start!");

  client.setServer(mqttServer, 1883);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);

  // Read temperature
  float temp = dht.readTemperature();

  // Read humidity
  float hum = dht.readHumidity();

  // Check if no data send
  if(isnan(hum) || isnan(temp)){
    Serial.println("Failed to read temperature and humidity data from sensor!");
    return;
  }

  // Read temperature
  Serial.print("Temperature : ");
  Serial.print(temp);
  Serial.println(" C");

  // Read humidity
  Serial.print("Humidity : ");
  Serial.println(hum);
}

// WiFi Setup function
void setupWifi(){
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

// Reconnect function
void reconnect(){
  while (!client.connected()){
    if(client.connect("ESP32Client")) {
      client.subscribe("esp32/data");
    } else {
      delay(5000);
    }
  }
}