#include <Arduino.h>
#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Define sensor type and pin
#define DHTTYPE DHT22
int sensorPin = 18;

// WiFi configuration
const char* ssid = "odoxs";
const char* password = "kingking04";
const char* mqttServer = "192.168.1.14"; // Change into Raspberry Pi IP

// Define struct configuration
WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(sensorPin, DHTTYPE);

void reconnect(){
  // Loop until connected
  while(!client.connected()){
    if(client.connect("ESP32Client")){
      Serial.println("Connected to MQTT broker");
    } else {
      delay(5000);
      Serial.print(".");
    }
  }
}

// Create read sensor function and publish data into MQTT broker
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

  // Read RSSI
  int rssi = WiFi.RSSI();

  // Publish temperature and humidity data
  String payload = String("Temperature: ") + String(temp) + " C, Humidity: " + String(hum) + " %, RSSI: " + String(rssi) + " dBm";
  client.publish("iot/data/esp32_1", payload.c_str());

  Serial.print("Data sent to MQTT broker: ");
  Serial.println(payload);

  delay(2000);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // Configure setup for wifi, MQTT connection and sensors
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Connecting to WiFi...");
    delay(1000);
  }
  client.setServer(mqttServer, 1883);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
    reconnect();
  }
  client.loop();
  readSensorData();
}
