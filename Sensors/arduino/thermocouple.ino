/***************************************************
  This is an example for the Adafruit Thermocouple Sensor w/MAX31855K

  Designed specifically to work with the Adafruit Thermocouple Sensor
  ----> https://www.adafruit.com/products/269

  These displays use SPI to communicate, 3 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <SPI.h>
#include "Adafruit_MAX31855.h"

// Default connection is using software SPI, but comment and uncomment one of
// the two examples below to switch between software SPI and hardware SPI:

// Example creating a thermocouple instance with software SPI on any three
// digital IO pins.
#define MAXDO1   2
#define MAXCS1   3
#define MAXCLK1  4
#define MAXDO2   5 
#define MAXCS2   6
#define MAXCLK2  7

// initialize the Thermocouple
Adafruit_MAX31855 thermocouple1(MAXCLK1, MAXCS1, MAXDO1);
Adafruit_MAX31855 thermocouple2(MAXCLK2, MAXCS2, MAXDO2);

// Example creating a thermocouple instance with hardware SPI
// on a given CS pin.
//#define MAXCS   10
//Adafruit_MAX31855 thermocouple(MAXCS);

// Example creating a thermocouple instance with hardware SPI
// on SPI1 using specified CS pin.
//#define MAXCS   10
//Adafruit_MAX31855 thermocouple(MAXCS, SPI1);

void setup() {
  Serial.begin(9600);

  while (!Serial) delay(1); // wait for Serial on Leonardo/Zero, etc

  Serial.println("MAX31855 test");
  // wait for MAX chip to stabilize
  delay(500);
  Serial.print("Initializing sensor...");
  if (!thermocouple1.begin()) {
    Serial.println("ERROR IN 1");
    while (1) delay(10);
  }
  if (!thermocouple2.begin()) {
    Serial.println("ERROR IN 2");
    while (1) delay(10);
  }

  // OPTIONAL: Can configure fault checks as desired (default is ALL)
  // Multiple checks can be logically OR'd together.
  // thermocouple.setFaultChecks(MAX31855_FAULT_OPEN | MAX31855_FAULT_SHORT_VCC);  // short to GND fault is ignored

  Serial.println("DONE.");
}

void loop() {
  // basic readout test, just print the current temp
   Serial.print("Internal Temp1 = ");
   Serial.println(thermocouple1.readInternal());
   Serial.print("Internal Temp2 = ");
   Serial.println(thermocouple2.readInternal());

   double c1 = thermocouple1.readCelsius();
   double c2 = thermocouple2.readCelsius();
   if (isnan(c1)||isnan(c2)) {
     Serial.println("Thermocouple 1 fault(s) detected!");
     uint8_t e1 = thermocouple1.readError();
     uint8_t e2 = thermocouple2.readError();
     if (e1 & MAX31855_FAULT_OPEN) Serial.println("FAULT: Thermocouple 1 is open - no connections.");
     if (e1 & MAX31855_FAULT_SHORT_GND) Serial.println("FAULT: Thermocouple 1 is short-circuited to GND.");
     if (e1 & MAX31855_FAULT_SHORT_VCC) Serial.println("FAULT: Thermocouple 1 is short-circuited to VCC.");
     if (e2 & MAX31855_FAULT_OPEN) Serial.println("FAULT: Thermocouple 2 is open - no connections.");
     if (e2 & MAX31855_FAULT_SHORT_GND) Serial.println("FAULT: Thermocouple 2 is short-circuited to GND.");
     if (e2 & MAX31855_FAULT_SHORT_VCC) Serial.println("FAULT: Thermocouple 2 is short-circuited to VCC.");
   } 
   else {
     Serial.print("C1 = ");
     Serial.println(c1);
     Serial.print("C2 = ");
     Serial.println(c2);
   }
   //Serial.print("F = ");
   //Serial.println(thermocouple.readFahrenheit());

   delay(1000);
}