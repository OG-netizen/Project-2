#include <Arduino.h>

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>

#define RightMotorSpeed 5
#define RightMotorDir   0 
#define LeftMotorSpeed  4
#define LeftMotorDir    2
#define echoPin 14 // attach pin D5 Arduino to pin Echo of HC-SR04
#define trigPin 12 //attach pin D6 Arduino to pin Trig of HC-SR04
#define IRSensorRight 13 // attach pin D7 Arduino pin naar to Right IR 
#define IRSensorLeft 15 // attach  pin D8 Arduino pin to left IR

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
char auth[] = "BlynToken";
char ssid[] = "your ssid";
char pass[] = "wifi password";

int minRange = 312;
int maxRange = 712;

int minSpeed = 450;
int maxSpeed = 1020;
int noSpeed = 0;


void moveControl(int x, int y)
{

  if(y >= maxRange && x >= minRange && x <= maxRange) //zataci R
  {
    digitalWrite(RightMotorDir,HIGH); 
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
  }
 
  // move forward right
  else if(x >= maxRange && y >= maxRange)   //zataci R
  {
    digitalWrite(RightMotorDir,HIGH);
    digitalWrite(LeftMotorDir,HIGH);
   analogWrite(RightMotorSpeed,minSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
  }

  // move forward left
  else if(x <= minRange && y >= maxRange)
  {
    digitalWrite(RightMotorDir,HIGH);
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,minSpeed);
  }

  // neutral zone
  else if(y < maxRange && y > minRange && x < maxRange && x > minRange)
  {
    analogWrite(RightMotorSpeed,noSpeed);
    analogWrite(LeftMotorSpeed,noSpeed);
  }

 // move back
  else if(y <= minRange && x >= minRange && x <= maxRange)
  {
    digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,LOW);
   analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
  }

  // move back and right
 else if(y <= minRange && x <= minRange)
  {
   digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,LOW);
    analogWrite(RightMotorSpeed,minSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed); 
  }

  // move back and left
  else if(y <= minRange && x >= maxRange)
  {
    digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,LOW);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,minSpeed);
  }
}

void reverse(){

  digitalWrite(RightMotorDir,HIGH);
    digitalWrite(LeftMotorDir,LOW);
   analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
}

void forward(){

  digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,HIGH);
   analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);

  
}

void stopMoving(){

   analogWrite(RightMotorSpeed,noSpeed);
   analogWrite(LeftMotorSpeed,noSpeed);
  
}

void ultrasonicDetection(){

   // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)


}



void setup()
{
  Serial.begin(9600);
 
 
  // initial settings for motors off and direction forward
  pinMode(RightMotorSpeed, OUTPUT);
  pinMode(LeftMotorSpeed, OUTPUT);
  pinMode(RightMotorDir, OUTPUT);
  pinMode(LeftMotorDir, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(IRSensorLeft,INPUT);
  pinMode(IRSensorRight,INPUT);
 
  digitalWrite(RightMotorSpeed, LOW);
  digitalWrite(LeftMotorSpeed, LOW);
  digitalWrite(RightMotorDir, HIGH);
  digitalWrite(LeftMotorDir,HIGH);

 
 }




void loop()
{
  ultrasonicDetection();

  if (distance < 7){
    stopMoving();
  }else{
    forward();
  }
  
  if(){
  }

 
}






