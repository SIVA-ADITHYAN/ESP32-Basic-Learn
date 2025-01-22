#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

// Initialize the GPS
TinyGPSPlus gps;
HardwareSerial ss(2); // Use hardware serial 2 (GPIO 16 and GPIO 17)

// Initialize the LCD with the I2C address 0x27, 16 columns, and 2 rows
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  // Start serial communication for debugging purposes
  Serial.begin(115200);
  // Start serial communication with GPS module
  ss.begin(9600, SERIAL_8N1, 16, 17); // RX pin 16, TX pin 17

  // Initialize the LCD
  lcd.init();
  lcd.backlight();

  // Display a startup message
  lcd.setCursor(0, 0);
  lcd.print("GPS Initializing");
}

void loop() {
  // Check if data is available from the GPS module
  if (ss.available() > 0) {
    char c = ss.read();
    gps.encode(c);
  }
  
  // Check if the GPS location data has been updated
  if (gps.location.isUpdated()) {
    // Clear the LCD
    lcd.clear();
    
    // Display latitude
    lcd.setCursor(0, 0);
    lcd.print("Lat: ");
    lcd.print(gps.location.lat(), 6);

    // Display longitude
    lcd.setCursor(0, 1);
    lcd.print("Lon: ");
    lcd.print(gps.location.lng(), 6);

    // Print the data to the serial monitor for debugging
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
  }
}
