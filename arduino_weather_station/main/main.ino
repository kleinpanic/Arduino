/*
 * DHT11 Module:
 * Sig  <->  2
 * VCC  <->  5V
 * GND  <->  GND
 *
 * BH1750FVI:
 * VCC  <->  3V3
 * GND  <->  GND
 * SCL  <->  A5
 * SDA  <->  A4
 * ADD  <->  floating
 *
 * BMP180:
 * VCC  <->  5V
 * GND  <->  GND
 * SCL  <->  A5
 * SDA  <->  A4
 */

#include "DHT.h"
// #include "BH1750FVI.h"
#include <Wire.h>
#include "SFE_BMP180.h"

#define DHT11_PIN 2
DHT dht11(DHT11_PIN, DHT11);

// BH1750FVI bh1750(BH1750FVI::k_DevModeContLowRes);

SFE_BMP180 bmp180;


void show_headers()
{
    Serial.print("Temperature (°F)");
    Serial.print("\t");
    Serial.print("Relative Humidity (%)");
    Serial.print("\t");
    // Serial.print("Illuminance (lx)");
    Serial.print("\t");
    Serial.print("Pressure (mb)");
    Serial.println();
}

void get_temperature()
{
    float temperature = dht11.readTemperature(true); // fahrenheit
    Serial.print(temperature);
}

void get_humidity()
{
    float humidity  = dht11.readHumidity();
    Serial.print(humidity);
}

/*
void get_illuminance()
{
    uint16_t illuminance = bh1750.GetLightIntensity();
    Serial.print(illuminance);
}
*/

void get_pressure()
{
    char status;
    double pressure, temperature;

    status = bmp180.startTemperature();
    delay(status);
    status = bmp180.getTemperature(temperature);

    status = bmp180.startPressure(3);
    delay(status);
    status = bmp180.getPressure(pressure, temperature);

    Serial.print(pressure);
}

void setup() {
    Serial.begin(9600);

    // initialize sensors 
    dht11.begin();
    // bh1750.begin();

    if (bmp180.begin())
        Serial.println("[log] BMP180 init success");
    else
        Serial.println("[log] BMP180 init fail");

    show_headers();
}

void loop() {
    // readings
    get_temperature(); Serial.print("\t");
    get_humidity(); Serial.print("\t");
    // get_illuminance(); Serial.print("\t");
    get_pressure(); // Serial.print("\t");

    Serial.println();

    // interval between measurements;
    delay(1000);
}

