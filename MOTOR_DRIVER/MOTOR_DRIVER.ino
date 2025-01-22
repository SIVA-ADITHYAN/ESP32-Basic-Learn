#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3TFhcDrvW"
#define BLYNK_TEMPLATE_NAME "Motor ON"
#define BLYNK_AUTH_TOKEN "1j6XzAKXMxJoy2_O0VLKOXBhzWIED3lT"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "1j6XzAKXMxJoy2_O0VLKOXBhzWIED3lT";  // Replace with your Blynk Auth Token
char ssid[] = "IOT";       // Replace with your Wi-Fi SSID
char pass[] = "123456789";   // Replace with your Wi-Fi password

const int m1 = 2;           // GPIO pin where the LED is connected
const int m2 = 15;
const int m3 = 4;
const int m4 = 18;
 
void setup()
{
  // Debug console
  Serial.begin(115200);

  // Set up the LED pin as an output
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(m3,OUTPUT);
  pinMode(m4,OUTPUT);

  // Connect to Wi-Fi and Blynk
  Blynk.begin(auth, ssid, pass);
}

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // Get the value from the Blynk app

  // Turn the LED on or off based on the button state
  digitalWrite(m1, pinValue);
  digitalWrite(m3, pinValue);
  
}

BLYNK_WRITE(V2)
{
  int pinValue=param.asInt();
  digitalWrite(m2,pinValue);
  digitalWrite(m4,pinValue);
}
BLYNK_WRITE(V3)
{
  int pinValue=param.asInt();
  digitalWrite(m1,pinValue);
  digitalWrite(m2,pinValue);
}
BLYNK_WRITE(V4)
{
  int pinValue=param.asInt();
  digitalWrite(m3,pinValue);
  digitalWrite(m4,pinValue);
}
void loop()
{
  Blynk.run();
}
