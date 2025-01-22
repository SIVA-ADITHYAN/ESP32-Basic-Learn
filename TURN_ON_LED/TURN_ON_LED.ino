#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3TFhcDrvW"
#define BLYNK_TEMPLATE_NAME "Motor ON"
#define BLYNK_AUTH_TOKEN "1j6XzAKXMxJoy2_O0VLKOXBhzWIED3lT"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "YourAuthToken";  // Replace with your Blynk Auth Token
char ssid[] = "YourSSID";       // Replace with your Wi-Fi SSID
char pass[] = "YourPassword";   // Replace with your Wi-Fi password

const int ledPin = 2;           // GPIO pin where the LED is connected

void setup()
{
  // Debug console
  Serial.begin(115200);

  // Set up the LED pin as an output
  pinMode(ledPin, OUTPUT);

  // Connect to Wi-Fi and Blynk
  Blynk.begin(auth, ssid, pass);
}

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // Get the value from the Blynk app

  // Turn the LED on or off based on the button state
  digitalWrite(ledPin, pinValue);
}

void loop()
{
  Blynk.run();
}
