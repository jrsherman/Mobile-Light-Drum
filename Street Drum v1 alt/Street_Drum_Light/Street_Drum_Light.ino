int colorCounter=0;
#include "Tlc5940.h"
int sensorPin = A0;
int sensorValue;
void setup() {
  Serial.begin(9600);
Tlc.init();
}

/*
int i = 4095;
while(i>0){
 Tlc.set(0, i);
  Tlc.update();
  Tlc.clear();

i--;
}
*/

void loop() {
 sensorValue = analogRead(sensorPin);
// Serial.println(sensorValue);
  if(sensorValue > 80){
   // Serial.println("trigger");
    delay(40);
      double i = 4095;
while(i>0){
 sensorValue = analogRead(sensorPin);
 if(colorCounter < 5)
    Tlc.set(2, i);
 else if (colorCounter >= 6)
    Tlc.set(1, i);
  Tlc.update();
  Tlc.clear();

i-=.5;
 if(sensorValue > 80&& i <= 4095){
    i=4095;
    //colorCounter++;
    Serial.println(colorCounter);
  }
}
colorCounter++;
  }
  Tlc.set(0, 0);
   Tlc.update();
  Tlc.clear();
  delay(25);
}
