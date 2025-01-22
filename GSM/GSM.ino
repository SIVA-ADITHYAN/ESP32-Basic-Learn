#include <HardwareSerial.h>

const int RX_PIN = 16;  // RX pin for ESP32 (connect to TX of GSM module)
const int TX_PIN = 17;  // TX pin for ESP32 (connect to RX of GSM module)

HardwareSerial sim800(1);  // Use hardware serial 1 for SIM800C communication

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(115200);
  delay(1000);

  // Initialize GSM module serial communication
  sim800.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  // Wait for GSM module to initialize
  delay(5000);

  // Check GSM module status
  checkGSMStatus();

  // Send SMS
  sendSMS("+919360504096", "Hello, this is a test message from ESP32!");
}

void loop() {
  // Display any incoming data from the GSM module in the serial monitor
  if (sim800.available()) {
    Serial.write(sim800.read());
  }
  if (Serial.available()) {
    sim800.write(Serial.read());
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
