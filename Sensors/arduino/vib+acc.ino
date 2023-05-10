#include <Wire.h>

#include <Adafruit_Sensor.h> 

#include <Adafruit_ADXL345_U.h>



Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

const int analogInPin = A3;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9;  // Analog output pin that the LED is attached to

int sensorValue = 0;  // value read from the pot
int outputValue = 0;

int LED_Pin = 13;
int vibr_Pin =3;

void setup(void) 

{
   pinMode(LED_Pin, OUTPUT);
   pinMode(vibr_Pin, INPUT); //set vibr_Pin input for measurment

   Serial.begin(9600);  

   if(!accel.begin())

   {

      Serial.println("No valid sensor found");

      while(1);

   }

}



long TP_init(){
  long measurement=pulseIn (vibr_Pin, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
} 

void loop(void) 

{

   sensors_event_t event; 

   accel.getEvent(&event);

   Serial.print(" "); Serial.print(event.acceleration.x); Serial.print("  ");
   Serial.print(" "); Serial.print(event.acceleration.y); Serial.print("  ");
   Serial.print(" "); Serial.print(event.acceleration.z); Serial.print("  ");

   long measurement =TP_init();

   Serial.print(" "); Serial.print(measurement); Serial.println(" ");
   
   if (measurement > 1000){
     digitalWrite(LED_Pin, HIGH);
   }
   else{
     digitalWrite(LED_Pin, LOW); 
   }
   
   delay(1000);

}