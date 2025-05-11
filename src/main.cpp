#include <Arduino.h>
#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <ESP32Ping.h>

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
IPAddress ip(192, 168, 1, 12); // Change into Raspberry Pi IP Address

// Define global variable for metrics measurement
unsigned long lastMillis = 0; // Last time data was sent
unsigned long latency = 0; // Store latency data
unsigned long throughput = 0; // Store throughput data

void setupWifi();
void pingServer();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // Configure setup for wifi, MQTT connection and sensors
  setupWifi();
  client.setServer(mqttServer, 1883);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);

  // Ping the server
  pingServer();
}

// Create read sensor function
void readSensorData(){
  // Read temperature
  float temp = dht.readTemperature();

  // Read humidity
  float hum = dht.readHumidity();

  // Check if no data being sended
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

// Create ping function
void pingServer(){
  // Ping the emas2.ui.ac.id 4 times
  Serial.println("Pinging the server...");
  bool ret = Ping.ping(ip, 4);

  // Check if ping is success
  if(ret){
  
  // Check the avg response time
  float avg_res_time_ms = Ping.averageTime();
  Serial.print("Average response time: ");
  Serial.print(avg_res_time_ms);
  Serial.println(" ms");
  } else {
    Serial.println("Ping failed!");
  }
}

// WiFi Setup function
void setupWifi(){
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print("WiFi Ip address: ");
  Serial.println(WiFi.localIP());
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