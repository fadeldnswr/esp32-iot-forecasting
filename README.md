# IoT Network Performance Monitoring with ESP32

## Project Description
This project aims to monitor IoT network performance between the ESP32 and Raspberry Pi by measuring several key network metrics: latency, packet loss, RSSI (Signal Strength), throughput, and sensor data from DHT22 (Temperature and Humidity). The collected data is sent to Raspberry Pi via MQTT, where it can be further analyzed for network monitoring and optimization.

### Metrics Measured
1. Latency: Measures the round-trip time it takes for data to travel from ESP32 to Raspberry Pi.
2. Packet Loss: Calculates the number of data packets lost during transmission.
3. RSSI (Signal Strength): Measures the Wi-Fi signal strength between ESP32 and Raspberry Pi.
4. Throughput: Measures the speed of data transfer in the network.
5. Temperature and Humidity (DHT22): Reads temperature and humidity data from the DHT22 sensor.

### Features
- Latency Measurement: Uses WiFi.ping() to measure round-trip time.
- Packet Loss: Calculates the number of lost packets based on sent and received data.
- RSSI (Signal Strength): Measures the received signal strength using WiFi.RSSI().
- Throughput: Measures the data transfer rate in the network.
- DHT22 Sensor Data: Reads temperature and humidity data from the DHT22 sensor periodically.

### Code Structure
1. **Latency Measurement**: The function measureLatency() calculates the round-trip time using WiFi.ping() to a designated IP (gateway or server).
2. **Packet Loss**: The function measurePacketLoss() calculates the difference between the total sent and received packets to compute packet loss.
3. **RSSI (Signal Strength)**: The function measureRSSI() uses WiFi.RSSI() to read the signal strength between ESP32 and the Wi-Fi router.
4. **Throughput**: The function measureThroughput() calculates the amount of data successfully transmitted within a certain period (e.g., 1 second).
5. **DHT22 Sensor**: The function measureSensorData() reads temperature and humidity from the DHT22 sensor and sends it to Raspberry Pi.
