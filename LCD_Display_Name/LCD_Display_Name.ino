
#include <LiquidCrystal_I2C.h>

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);  

void setup(){
  // initialize LCD
  lcd.begin();
  // turn on LCD backlight                      
  lcd.backlight();
}

void loop(){
  
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Hello");
  delay(1000);
  lcd.clear();
  // clears the display to print new message
  // set cursor to first column, second row
  lcd.setCursor(0,1);
  lcd.print("Hello");

}
