#include "Tlc5940.h"
int sensorPin = A0;
int sensorValue;
const int ledPin =  13;
 int devided;
int ledState = LOW; 
int timerOneSet;
int timerTwoSet;
unsigned long previousMillis = 0;
int runThrough = 0;
unsigned long setTimerOne=0;
unsigned long setTimerTwo;
int runThroughThing=0;
long interval; 
unsigned long int inputTimeDetection[13]={1000,1000,0,0,0,0,0,0,0,0,0,0,0};
int arrayCounter = 2;
void setup() {
  Serial.begin(9600);
  Tlc.init();
  delay(50);
}
void loop() {  
  
  
  sensorValue = analogRead(sensorPin);  
  if(sensorValue > 90){
    Serial.print("array counter: ");
    Serial.println(arrayCounter);
    long inputTime = millis();
    inputTimeDetection[arrayCounter]= inputTime;
    arrayCounter++;
    
    if(arrayCounter>12){
      runThroughThing = 1;
      arrayCounter = 0;}
    for(int i=0;i<13;i++){
      Serial.println(inputTimeDetection[i]);   
      }
    Serial.println("");
    delay(100);
  }
  if(inputTimeDetection[0]!=0&&inputTimeDetection[0]!=0){ 
  int inputSum=0;
    if(runThroughThing){
      devided = 12;
    }
    else
    {
      devided = arrayCounter;
    }
    for(int i=0;i<arrayCounter;i++){
      inputSum+=inputTimeDetection[i];
    }
    interval=inputSum/devided;   
    } 
    unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    Tlc.set(4,3000);
    Tlc.update();
    delay(25);
    Tlc.set(4,0);
    Tlc.update();
  }
  }

