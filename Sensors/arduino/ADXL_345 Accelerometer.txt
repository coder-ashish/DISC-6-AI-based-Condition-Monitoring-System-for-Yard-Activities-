#include <Wire.h>

#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(); 


 if(!accel.begin())

   {

      Serial.println("No valid sensor found");

      while(1);

   }
void loop(void) 

{

   sensors_event_t event; 

   accel.getEvent(&event);

   Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
   
   Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");

   Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");
}

   delay(1000);

}
