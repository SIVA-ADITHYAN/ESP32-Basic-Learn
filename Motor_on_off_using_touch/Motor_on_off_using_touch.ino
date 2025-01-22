#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3zTdGW1g6"
#define BLYNK_TEMPLATE_NAME "Motor ON OFF using DHT11"
#define BLYNK_AUTH_TOKEN "eHz8maaMlw-Rmte_Vruh96swwxSzS25y"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// WiFi credentials
char auth[] = "eHz8maaMlw-Rmte_Vruh96swwxSzS25y";
char ssid[] = "IOT";
char pass[] = "123456789";

// Blynk authentication token


// Pin definitions
const int relayPin = 32;          // Relay control pin
const int touchPin = 35;          // Touch sensor pin
const int gasSensorPin = 34;     // Analog pin for gas sensor

// Thresholds
const int gasThreshold = 2500;    // Gas sensor threshold value for motor activation

void setup() {
  Serial.begin(9600);

  // Connect to WiFi
  Blynk.begin(auth, ssid, pass);

  // Initialize pins
  pinMode(relayPin, OUTPUT);
  pinMode(touchPin, INPUT);
  
  // Uncomment these lines if using a DHT sensor
  // dht.begin();

  // Setup Blynk virtual pins
  Blynk.virtualWrite(V1, 0); // Initialize button state to off
}

void loop() {
  Blynk.run();

  // Read touch sensor state
  int touchState = digitalRead(touchPin);
  // Read gas sensor value
  int gasValue = analogRead(gasSensorPin);
  Serial.print(gasValue+"\n");

  // Display gas sensor value in Blynk
  Blynk.virtualWrite(V2, gasValue);

  // Check gas sensor threshold
  if (gasValue > gasThreshold) {
    Serial.println("Gas level high - Turning on motor");
    digitalWrite(relayPin, HIGH);  // Turn on motor
  } else {
    digitalWrite(relayPin, LOW);   // Turn off motor
  }
}

// Blynk app button handler
BLYNK_WRITE(V1) {
  int buttonState = param.asInt();

  if (buttonState == HIGH) {
    Serial.println("Button pressed - Turning on relay");
    digitalWrite(relayPin, HIGH);  // Turn on relay
  } 
  else
  {
    Serial.println("Button Released - Turning OFF relay");
    digitalWrite(relayPin, LOW);  // Turn on relay
  }
}
