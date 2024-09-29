#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2      // Define to which pin the sensor is connected
#define DHTTYPE DHT11 // Define the type of DHT sensor

DHT dht(DHTPIN, DHTTYPE);

// Initialize the LCD, address 0x27 is common for most I2C LCDs
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Initialize the LCD
  lcd.begin();
  lcd.backlight();
  lcd.print("Initializing...");
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.print("Sensor Error");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");

  // Clear the LCD and print the new values
  lcd.clear();
  lcd.setCursor(0, 0);  // Set cursor to the first column, first row
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print(" %");

  lcd.setCursor(0, 1);  // Set cursor to the first column, second row
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");
}
