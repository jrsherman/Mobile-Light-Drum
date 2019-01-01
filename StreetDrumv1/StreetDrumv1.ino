//The purpose of this code is to create a lightshow for street drum performances.
//If I am able to reclaim cost expedeture for creation it will be a project well worth.

//Things to do:
//Trigger Led on hit from the kick/
//programs:
//1: change color every hit on full for 1 second durration and continues if hit within that time frame


int colorCounter=0;
#include "Tlc5940.h"
int sensorPin = A0;
int sensorValue;
void setup() {
  Serial.begin(9600);
Tlc.init();
}
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
