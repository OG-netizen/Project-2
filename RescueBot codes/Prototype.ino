#include <Arduino.h>

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>

#define RightMotorSpeed 5
#define RightMotorDir   0 
#define LeftMotorSpeed  4
#define LeftMotorDir    2
#define echoPin 14 // attach pin D5 Arduino to pin Echo of HC-SR04
#define trigPin 12 //attach pin D6 Arduino to pin Trig of HC-SR04
#define IRSensorRight 15 // attach pin D7 Arduino pin naar to Right IR 
#define IRSensorLeft 13 // attach  pin D8 Arduino pin to  left IR

int state = 1;

long duration; // variable for the duration of sound wave travel
int distance,Right,Left = 0; 


char auth[] = "BlynToken";
char ssid[] = "your ssid";
char pass[] = "wifi password";

int minRange = 312;
int maxRange = 712;

int minSpeed = 200;
int maxSpeed = 600;
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

  digitalWrite(RightMotorDir,LOW);
  digitalWrite(LeftMotorDir,LOW);
  analogWrite(RightMotorSpeed,maxSpeed);
   analogWrite(LeftMotorSpeed,maxSpeed);
}

void forward(){

  digitalWrite(RightMotorDir,HIGH);
  digitalWrite(LeftMotorDir,HIGH);
  analogWrite(RightMotorSpeed,600);
  analogWrite(LeftMotorSpeed,600);

  
}

void stopMoving(){

   analogWrite(RightMotorSpeed,noSpeed);
   analogWrite(LeftMotorSpeed,noSpeed);
  
}

void forwardLeft(){

  digitalWrite(RightMotorDir,HIGH);
  digitalWrite(LeftMotorDir,HIGH);
  analogWrite(RightMotorSpeed,maxSpeed);
  analogWrite(LeftMotorSpeed, minSpeed);

}

void reverseLeft(){


   digitalWrite(RightMotorDir,LOW);
  digitalWrite(LeftMotorDir,LOW);
  analogWrite(RightMotorSpeed,maxSpeed);
   analogWrite(LeftMotorSpeed,minSpeed);

  
}


void reverseRight(){


   digitalWrite(RightMotorDir,LOW);
  digitalWrite(LeftMotorDir,LOW);
  analogWrite(RightMotorSpeed,minSpeed);
   analogWrite(LeftMotorSpeed,maxSpeed);

  
}

void forwardRight(){

  digitalWrite(RightMotorDir,HIGH);
  digitalWrite(LeftMotorDir,HIGH);
  analogWrite(RightMotorSpeed,minSpeed);
  analogWrite(LeftMotorSpeed,maxSpeed);


}


void TurnRight(){

  digitalWrite(RightMotorDir,HIGH);
  digitalWrite(LeftMotorDir,HIGH);
  analogWrite(RightMotorSpeed,0);
  analogWrite(LeftMotorSpeed,maxSpeed);


}


void TurnLeft(){

  digitalWrite(RightMotorDir,HIGH);
  digitalWrite(LeftMotorDir,HIGH);
  analogWrite(RightMotorSpeed,maxSpeed);
  analogWrite(LeftMotorSpeed,100);


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


void IR(){

  Right = digitalRead(IRSensorRight);
  Left = digitalRead(IRSensorLeft);

}

void DetermineForward(){  // function to determine positionn 

  if(distance < 15){

   
    TurnRight();
    delay(1500);
    forward();
    delay(500);
    forwardLeft();
    delay(1500);
    
    
  }else{

    forward();

  }

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
  
 digitalWrite(RightMotorDir,HIGH);

 
 }



void loop()
{
  ultrasonicDetection();
  IR();



 if (Right == 0 && Left == 0){

    DetermineForward();
    
  }else if(Right == 1 && Left == 0){
 
    forwardLeft();
    
   
  }else if(Right == 0 && Left == 1){
     
   forwardRight();
   
     
  }

   if(Right == 1 && Left == 1){

    if(state == 2){
      reverse();
      delay(2000);
      TurnLeft();
      delay(1500);
    }

    if(state == 1){ 

      reverse();
      delay(2000);
      TurnRight();
      delay(1500);
     

    }
    
   }
 
  
}