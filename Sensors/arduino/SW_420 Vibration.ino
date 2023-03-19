#include <Wire.h>

#include <Adafruit_Sensor.h> 




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

  
long TP_init(){
  long measurement=pulseIn (vibr_Pin, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
} 

}
void loop(void) 

{

 long measurement =TP_init();

   Serial.print("Vibration: "); Serial.print(measurement/1000.0); Serial.println(" Hz");
   
   if (measurement > 1000){
     digitalWrite(LED_Pin, HIGH);
   }
   else{
     digitalWrite(LED_Pin, LOW); 
   }
   
   delay(1000);

}




