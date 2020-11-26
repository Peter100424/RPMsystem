#include <SparkFunBME280.h>

/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor
  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650
  This sketch only supports the SPI bus for connection.
 ***************************************************************************/
#include <SparkFunBME280.h>
#include <SPI.h>
#include "cactus_io_BME280_SPI.h"

#define BME_SCK 13      // Serial Clock
#define BME_MISO 12     // Serial Data Out
#define BME_MOSI 11     // Serial Data In
#define BME_CS 10       // Chip Select

// Create the BME280 object
BME280_SPI bme(BME_CS,BME_MOSI,BME_MISO,BME_SCK);              

void setup() {
  Serial.begin(9600);
  Serial.println("Bosch BME280 Barometric Pressure - Humidity - Temp Sensor | cactus.io"); 

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  bme.setTempCal(-1);
  
  Serial.println("Pressure\tHumdity\t\tTemp\t\tTemp");
}

void loop() {

    bme.readSensor();
  
    Serial.print(bme.getPressure_MB()); Serial.print("\t\t");    // Pressure in millibars
    Serial.print(bme.getHumidity()); Serial.print("\t\t");
    Serial.print(bme.getTemperature_C()); Serial.print(" *C\t");
    Serial.print(bme.getTemperature_F()); Serial.println(" *F\t");

    // add a 2 second delay to slow down the output
    delay(2000);
}
