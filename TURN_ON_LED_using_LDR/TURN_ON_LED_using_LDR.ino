#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3TFhcDrvW"
#define BLYNK_TEMPLATE_NAME "Motor ON"
#define BLYNK_AUTH_TOKEN "1j6XzAKXMxJoy2_O0VLKOXBhzWIED3lT"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "1j6XzAKXMxJoy2_O0VLKOXBhzWIED3lT";  // Replace with your Blynk Auth Token
char ssid[] = "IOT1";       // Replace with your Wi-Fi SSID
char pass[] = "123456789";   // Replace with your Wi-Fi password

const int ledPin = 2;  // Pin for the LED
const int ldrPin = 4;  // Pin for the LDR sensor
const int virtualLedPin = V2;  // Virtual pin for the LED in Blynk app

void setup()
{
  // Debug console
  Serial.begin(115200);

  // Setup Blynk
  Blynk.begin(auth, ssid, pass);

  // Setup pin modes
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
}

void loop()
{
  // Read the LDR sensor
  int ldrValue = digitalRead(ldrPin);

  // If the LDR sensor reads high, turn on both LEDs
  if (ldrValue == HIGH) {
    digitalWrite(ledPin, HIGH);
    Blynk.virtualWrite(virtualLedPin, 255);  // Turn on virtual LED in Blynk app
  } else {
    digitalWrite(ledPin, LOW);
    Blynk.virtualWrite(virtualLedPin, 0);  // Turn off virtual LED in Blynk app
  }

  // Run Blynk
 // Blynk.run();
}
