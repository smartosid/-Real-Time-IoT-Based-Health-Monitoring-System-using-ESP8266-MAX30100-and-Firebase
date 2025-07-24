#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

// WiFi Credentials
#define WIFI_SSID "Maam"
#define WIFI_PASSWORD "123456789"

// Updated Firebase Configuration
#define FIREBASE_HOST "finalheart-f49c9-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "BnO2ivo4ZnKK14EMtDLjgCGa1kub9R2NXTqpWcP9"

// Firebase objects
FirebaseData firebaseData;
FirebaseConfig config;
FirebaseAuth auth;

// MAX30100 sensor
PulseOximeter pox;
unsigned long lastUpdate = 0;
const int UPDATE_INTERVAL = 1000; // milliseconds (interval for sending data to Firebase)

void onBeatDetected() {
  Serial.println("Beat Detected!");
}

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");
  Serial.println(WiFi.localIP());

  // Firebase setup
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // MAX30100 init
  if (!pox.begin()) {
    Serial.println("MAX30100 init failed. Check wiring!");
    while (1);
  }

  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);  // Setting LED current
  pox.setOnBeatDetectedCallback(onBeatDetected);

  Serial.println("MAX30100 Initialized");
}

void loop() {
  pox.update();  // Continuously update MAX30100 sensor readings

  // Send data at fixed intervals (every second)
  if (millis() - lastUpdate >= UPDATE_INTERVAL) {
    int bpm = (int)pox.getHeartRate();  // Get current BPM from MAX30100
    int spo2 = (int)pox.getSpO2();     // Get current SpO2 from MAX30100

    // Output readings to Serial Monitor
    Serial.print("BPM: ");
    Serial.print(bpm);
    Serial.print(" | SpO2: ");
    Serial.print(spo2);
    Serial.println("%");

    // Only send valid readings (bpm > 0 and spo2 > 0)
    if (bpm > 0 && spo2 > 0) {
      sendToFirebase("/max30100/bpm", bpm);    // Send BPM to Firebase
      sendToFirebase("/max30100/spo2", spo2);  // Send SpO2 to Firebase
    }

    lastUpdate = millis();  // Update the timestamp for next sending
  }

  // No blocking delay, only process sensor updates and Firebase
  delay(10);  // Small delay to keep the loop responsive
}

void sendToFirebase(const String &path, int value) {
  if (Firebase.setInt(firebaseData, path, value)) {
    Serial.print("✅ Sent to Firebase ");
    Serial.print(path);
    Serial.print(": ");
    Serial.println(value);
  } else {
    Serial.print("❌ Firebase error: ");
    Serial.println(firebaseData.errorReason());
  }
}
