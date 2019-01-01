//v2 cycles through red green blue whilst building them until after blue it shuts off again and clears everything



//The purpose of this code is to create a lightshow for street drum performances.
//If I am able to reclaim cost expedeture for creation it will be a project well worth.
//Things to do:
//Trigger Led on hit from the kick/
//programs:
//1: change color every hit on full for 1 second durration and continues if hit within that time frame
//every time a hit is triggred turn off the sensing for a sec b.x there are mini hits due to the drum elasticity
#include "Tlc5940.h"
int piezoPinAssign = A0; //assigns pin0 on arduino to be input for piezo Sensor
int sensorData;
int lowPassThreshold = 80;
int tlcResolution = 4095;
int colorSelector = 0;

void setup(){
  Serial.begin(9600);//Allows for use of chars and strings as output in serial
  Tlc.init();//initializes the tlc5940 breakout
}
void loop(){
  sensorData = analogRead(piezoPinAssign);//Retrieves hit data from the kick drum through the piezoPinAssigg and snds it to sensor data for safe keeping.
  Serial.println(colorSelector);
  if(sensorData > lowPassThreshold){//Set lPT so tiny knocks don't trigger the light.
    if(colorSelector==0)
      Tlc.set(4,3500);
    else if(colorSelector==1)
      Tlc.set(2,3500);
    else if(colorSelector==2)
      Tlc.set(0,3500);
    else if(colorSelector==3){
      Tlc.set(0,0);
      Tlc.set(2,0);
      Tlc.set(4,0);
      colorSelector=-1;
    }
    Tlc.update();
    /*
    Tlc.update();
    Tlc.clear();
    */
    colorSelector++;
    delay(100);
   }
}
