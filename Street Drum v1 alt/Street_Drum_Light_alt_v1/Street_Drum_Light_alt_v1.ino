#include "Tlc5940.h"
int sensorPin = A0;
int sensorValue;

const int ledPin =  13;      // the number of the LED pin

// Variables will change :
int ledState = LOW;             // ledState used to set the LED
int timerOneSet;
int timerTwoSet;
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

unsigned long setTimerOne=0;
unsigned long setTimerTwo;
// constants won't change :
const long interval = 1000;           // interval at which to blink (milliseconds)
void setup() {
  Serial.begin(9600);
  Tlc.init();
  delay(25);
}
void loop() {
  sensorValue = analogRead(sensorPin);
  
  if(sensorValue > 90){  
    if(setTimerOne==0){
      setTimerOne = millis();
      timerOneSet=1;
    }
    else if(timerTwoSet!=3){
      timerTwoSet=1;
      setTimerTwo = millis();
  
    }
    delay(100);
  }
  if(timerOneSet==1){
    Tlc.set(0, 3000);
    Tlc.update();
    delay(20);
    Tlc.set(0,0);
    Tlc.update();
    timerOneSet=3;
  }
  if(timerTwoSet==1){
    Tlc.set(0, 3000);
    Tlc.update();
    delay(20);
    Tlc.set(0,0);
    Tlc.update();
    timerTwoSet=3;
  }
   unsigned long currentMillis = millis();
  
  if ((currentMillis - previousMillis >= setTimerTwo-setTimerOne)&&(timerTwoSet==3)&&(timerOneSet==3)){
    previousMillis = currentMillis;
     Tlc.set(0, 3000);
    Tlc.update();
    delay(20);
    Tlc.set(0,0);
    Tlc.update();

    
  }
}
