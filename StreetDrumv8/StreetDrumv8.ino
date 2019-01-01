//v5 adds the color table and a scaling function to return tlc required values
//The purpose of this code is to create a lightshow for street drum performances.
//If I am able to reclaim cost expedeture for creation it will be a project well worth.
//Things to do:
//Trigger Led on hit from the kick/
//programs:
//1: change color every hit on full for 1 second durration and continues if hit within that time frame
//every time a hit is triggred turn off the sensing for a sec b.x there are mini hits due to the drum elasticity
int onOffPattern[16][4] = {{0,0,0,0},{0,0,0,1},{0,0,1,0},
{0,0,1,1},{0,1,0,0},{0,1,0,1},{0,1,1,0},{0,1,1,1},{1,0,0,0},{1,0,0,1},{1,0,1,0},
{1,0,1,1},{1,1,0,0},{1,1,0,1},{1,1,1,0},{1,1,1,1}};
int selectPattern=0;
int selectElementInPattern=0;


#include "Tlc5940.h"
#include "colorValues.h"
int piezoPinAssign = A0; //assigns pin0 on arduino to be input for piezo Sensor
int sensorData;
int lowPassThreshold = 80;
int tlcResolution = 4095;
int colorSelector = 0;
int colorTableSelect =0;
//timer section below
unsigned long previousMillis = 0; 
const long interval = 3000;
int lightOn = 0;

unsigned long drumHitsInSeshin=0;

void setup(){
  Serial.begin(9600);//Allows for use of chars and strings as output in serial
  Tlc.init();//initializes the tlc5940 breakout
}
void loop(){
   
  sensorData = analogRead(piezoPinAssign);//Retrieves hit data from the kick drum through the piezoPinAssigg and snds it to sensor data for safe keeping.
  //Serial.println(colorSelector);
  if(sensorData > lowPassThreshold){//Set lPT so tiny knocks don't trigger the light.

    if(onOffPattern[selectPattern][selectElementInPattern]==1){ 
      lightOn=1;
      Tlc.set(4,scaledLedValue(colorSelector,0));
      Tlc.set(2,scaledLedValue(colorSelector,1));
      Tlc.set(0,scaledLedValue(colorSelector,2));
      Tlc.update();
      colorSelector++;
      previousMillis= millis();
      
    }
    
    Serial.println(selectElementInPattern);
    drumHitsInSeshin++;
    
    selectElementInPattern++;

    
    if(selectElementInPattern>3){
      selectElementInPattern=0;
      selectPattern++;
    }
    if(selectPattern>=15){
      selectPattern=0;
    }
    delay(100);
   }
  unsigned long currentMillis = millis();
  if ((currentMillis - previousMillis >= interval)&&(lightOn)) {
    // save the last time you blinked the LED
      Tlc.set(0,0);
      Tlc.set(2,0);
      Tlc.set(4,0);
      Tlc.update();
      //Serial.println("triggered");
    previousMillis = currentMillis;
    lightOn=0;
  }


   
}
