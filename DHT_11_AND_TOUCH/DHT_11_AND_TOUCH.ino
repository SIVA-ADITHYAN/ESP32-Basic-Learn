#define BLYNK_TEMPLATE_ID "TMPL3zTdGW1g6"
#define BLYNK_DEVICE_NAME "Motor ON OFF using DHT11"
#define BLYNK_AUTH_TOKEN "TVgK4THzjdBqw_cCpRthxJGK-mDCVRXS"

// Include necessary libraries
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#define DHTPIN 15 // Pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);

// Define touch sensor and motor (relay) pins
const int touchPin = 4;
const int motorPin = 5;

bool motorState = false; // Track the motor state

// Your WiFi credentials
char ssid[] = "IOT";       // Replace with your Wi-Fi SSID
char pass[] = "123456789";   // Replace with your Wi-Fi password

BlynkTimer timer;

void checkTouchSensor() {
  if (touchRead(touchPin) < 20) { // Adjust the threshold as needed
    motorState = !motorState;
    digitalWrite(motorPin, motorState ? HIGH : LOW);
    Blynk.virtualWrite(V1, motorState ? "ON" : "OFF"); // Update Blynk app
    delay(500); // Debounce delay
  }
}

void checkTemperature() {
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Read temperature as Celsius

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V2, t); // Update temperature on Blynk app
  Blynk.virtualWrite(V3, h); // Update humidity on Blynk app

  // If temperature is above a threshold, turn on the motor
  if (t > 30) { // Adjust the threshold as needed
    digitalWrite(motorPin, HIGH);
    Blynk.virtualWrite(V1, "ON"); // Update Blynk app
  } else if (!motorState) {
    digitalWrite(motorPin, LOW);
    Blynk.virtualWrite(V1, "OFF"); // Update Blynk app
  }
}

BLYNK_WRITE(V4) {
  motorState = param.asInt();
  digitalWrite(motorPin, motorState ? HIGH : LOW);
  Blynk.virtualWrite(V1, motorState ? "ON" : "OFF"); // Update Blynk app
}

void setup() {
  // Debug console
  Serial.begin(115200);

  // Setup pin modes
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW); // Ensure motor is off initially

  pinMode(touchPin, INPUT);

  // Initialize DHT sensor
  dht.begin();

  // Connect to WiFi and Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Set up timers
  timer.setInterval(100L, checkTouchSensor);
  timer.setInterval(2000L, checkTemperature); // Check temperature every 2 seconds
}

void loop() {
  Blynk.run();
  timer.run();
}
