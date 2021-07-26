#include <Servo.h>

String message;

Servo thr_left;
Servo thr_right;
Servo thr_vertical;


void setup() 
{
  thr_left.attach(3); //horizontal
  thr_right.attach(6); //vertical
  thr_vertical.attach(5);  //horizontal
  
  Serial.begin(9600);
  pinMode(13, OUTPUT); 
  
  thr_left.writeMicroseconds(1500);
  thr_right.writeMicroseconds(1500); 
  thr_vertical.writeMicroseconds(1500);
}

void loop() 
{
  while (Serial.available()) 
  {  
 
    char incomingChar = Serial.read();
    if (incomingChar == '1') 
      {
        Serial.println('1');
       thr_left.writeMicroseconds(1600);
       delay(2000);
       thr_left.writeMicroseconds(1500);
       message = "";
      }
    if (incomingChar == '2') 
      {
      Serial.println('2');
      thr_right.writeMicroseconds(1600);
      delay(2000);
      thr_right.writeMicroseconds(1500);
       message = "";
      }
     if(incomingChar == '3')
     {
      Serial.println('3');
      thr_vertical.writeMicroseconds(1600);
      delay(2000);
      thr_vertical.writeMicroseconds(1500);
       message = "";
     }
  }
}
