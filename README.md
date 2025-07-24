# Real-Time-IoT-Based-Health-Monitoring-System-using-ESP8266-MAX30100-and-Firebase

Real-Time IoT-Based Health Monitoring System using ESP8266, MAX30100, and Firebase

This project is a **cloud-connected IoT health monitoring system** that continuously reads **heart rate (BPM)** and **blood oxygen level (SpO₂)** using the **MAX30100 pulse oximeter sensor** and transmits the data in **real-time to Firebase Realtime Database** via an **ESP8266 (NodeMCU)**. It demonstrates a scalable, smart healthcare solution suitable for remote patient monitoring and emergency alert systems.

---

## 🚀 Key Features

- 📡 **Wi-Fi Enabled**: Uses ESP8266 to connect to the internet and push data to Firebase.
- ❤️ **Real-time Heartbeat & SpO₂ Monitoring**: Measures vital signs using MAX30100 sensor.
- ☁️ **Firebase Integration**: Sends data to Firebase Realtime Database for visualization and storage.
- 🔁 **Interval-Based Updates**: Sends data every second without blocking main loop.
- 🔔 **Beat Detection Alerts**: Logs heartbeats with optional integration for alerts (SMS/email/dashboard).
- 🧩 **Modular Design**: Easily expandable for more sensors or mobile dashboards.

---

## 🔧 Components Used

| Component          | Description                                |
|-------------------|--------------------------------------------|
| ESP8266 NodeMCU    | Microcontroller with built-in Wi-Fi       |
| MAX30100 Sensor    | Pulse oximeter and heart rate sensor      |
| Firebase Realtime DB | Cloud database for data logging         |
| Jumper Wires       | For connections                           |
| Micro USB Cable    | For programming NodeMCU                   |
| Breadboard (opt.)  | For prototyping                           |

---

## 🧠 System Architecture

1. MAX30100 reads **BPM** and **SpO₂**.
2. ESP8266 continuously reads sensor data and connects to Wi-Fi.
3. Data is pushed to **Firebase Realtime Database** under `/max30100/`.
4. Data can be monitored live via Firebase or a custom web dashboard.

---

## 📁 Folder Structure

health-monitoring/
├── firebase-config.txt # Firebase URL & auth token
├── MAX30100_ESP8266.ino # Main Arduino sketch
├── README.md # This file

yaml
Copy code

---

## 📊 Sample Firebase Data Format

```json
{
  "max30100": {
    "bpm": 78,
    "spo2": 96
  }
}

BPM: 78 | SpO2: 97%
✅ Sent to Firebase /max30100/bpm: 78
✅ Sent to Firebase /max30100/spo2: 97
Beat Detected!
🧩 Possible Extensions
📱 Integrate with Android App via Firebase SDK

📊 Add charts using Firebase + Web Dashboard (Chart.js, React, etc.)

📤 Send alerts via SMS/Email when BPM or SpO2 go beyond threshold

💾 Log historical data and visualize using Grafana or InfluxDB

🧠 Use AI/ML to detect health anomalies from patterns

