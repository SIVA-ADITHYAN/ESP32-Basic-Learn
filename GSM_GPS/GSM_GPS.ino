#include <HardwareSerial.h>
#include <TinyGPS++.h>

const int RX_PIN = 3;  // RX pin for ESP32 (co1nnect to TX of GSM module)
const int TX_PIN = 1;  // TX pin for ESP32 (connect to RX of GSM module)
const int GPS_RX_PIN = 16;  // RX pin for GPS module
const int GPS_TX_PIN = 17;  // TX pin for GPS module

HardwareSerial sim800(1);  // Use hardware serial 1 for SIM800C communication
HardwareSerial gpsSerial(2);  // Use hardware serial 2 for GPS communication

TinyGPSPlus gps;  // Create a TinyGPS++ object

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(115200);
  delay(1000);

  // Initialize GSM module serial communication
  sim800.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  // Initialize GPS module serial communication
  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);

  // Wait for GSM module to initialize
  delay(5000);

  // Check GSM module status
  checkGSMStatus();
}

void loop() {
  // Read data from the GPS module
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  // Display any incoming data from the GSM module in the serial monitor
  if (sim800.available()) {
    Serial.write(sim800.read());
  }
  if (Serial.available()) {
    sim800.write(Serial.read());
  }

  // Check if GPS location is valid and send SMS
  if (gps.location.isUpdated()) {
    String message = "Latitude: " + String(gps.location.lat(), 6) + ", Longitude: " + String(gps.location.lng(), 6);
    sendSMS("+919360504096", message);
    delay(60000);  // Wait for 1 minute before sending another SMS
  }
}

void checkGSMStatus() {
  sim800.println("AT");
  delay(1000);
  while (sim800.available()) {
    Serial.write(sim800.read());
  }

  sim800.println("AT+CSQ");
  delay(1000);
  while (sim800.available()) {
    Serial.write(sim800.read());
  }

  sim800.println("AT+CREG?");
  delay(1000);
  while (sim800.available()) {
    Serial.write(sim800.read());
  }
}

void sendSMS(String phoneNumber, String message) {
  sim800.println("AT+CMGF=1");  // Set SMS text mode
  delay(1000);
  while (sim800.available()) {
    Serial.write(sim800.read());
  }

  sim800.print("AT+CMGS=\"");
  sim800.print(phoneNumber);
  sim800.println("\"");
  delay(1000);
  while (sim800.available()) {
    Serial.write(sim800.read());
  }

  sim800.print(message);
  delay(1000);
  sim800.write(26);  // ASCII code for CTRL+Z to send the message
  delay(1000);
  while (sim800.available()) {
    Serial.write(sim800.read());
  }
}
