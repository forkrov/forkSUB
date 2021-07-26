#include <Servo.h>

#define MOTOR_STOP 1500
String message;

Servo thr_left;
Servo thr_right;
Servo thr_vertical;

int thr_left_dir = 1; //0-revers
int thr_right_dir = 1; //0-revers
int thr_vertical_dir = 1; // 0 -revers

float thr_left_k = 0.7; // 0.1 ..1
float thr_right_k = 1; // 0.1..1

void move_linear(int spd);
void rotate(int spd);
void diving(int spd);

unsigned long time_out1 = 200;
unsigned long time_out2 = 1000;

unsigned long timer_1,timer_2,timer_3;

int led_state = HIGH;

int counter;
int state = 0;

void setup() 
{
  Serial.begin(9600);
  
  thr_left.attach(3); //horizontal
  thr_right.attach(6); //vertical
  thr_vertical.attach(5);  //horizontal
  
  thr_left.writeMicroseconds(MOTOR_STOP);
  thr_right.writeMicroseconds(MOTOR_STOP); 
  thr_vertical.writeMicroseconds(MOTOR_STOP);
  delay(2000);
  timer_1 = millis();
  timer_2 = millis();
}

void loop() 
{
  if(millis()-timer_1>time_out1)
    {
      timer_1 = millis();
      digitalWrite(13, led_state);
      led_state = !led_state;
    }
  while (Serial.available()) 
  {  
    char incomingChar = Serial.read();
      if (incomingChar == '0') 
        {
          Serial.println("stop");
          move_linear(0);
          diving(0);
          message = "";
        }
      if (incomingChar == '1') 
        {
          Serial.println("goooo");
          move_linear(250);
          message = "";
        }
       if (incomingChar == '2') 
        {
          Serial.println("revers");
          move_linear(250);
          message = "";
        }
      if(incomingChar == '3')
     {
      Serial.println("dive");
      diving(250);
       message = "";
     }
    if(incomingChar == '4')
     {
      Serial.println("up");
      diving(-250);
       message = "";
     }
     if(incomingChar == '5')
     {
      Serial.println("rotate right");
      rotate(100);
       message = "";
     }
     if(incomingChar == '6')
     {
      Serial.println("rotate left");
      rotate(-100);
       message = "";
     }
  }
}

void move_linear(int spd)
{
  if((spd<400)&&(spd>-400))
  {
  int thr_left_speed = spd;
  int thr_right_speed = spd;
  if(thr_left_dir == 0)
    {
      thr_left_speed = -spd;
    }
  if(thr_right_dir == 0)
    {
      thr_right_speed = -spd;
    }
  thr_left.writeMicroseconds(int(MOTOR_STOP+(thr_left_speed*thr_left_k)));
  thr_right.writeMicroseconds(int(MOTOR_STOP+(thr_right_speed*thr_right_k)));
  }
}

void rotate(int spd)
{
  if((spd<200)&&(spd>-200))
  {
  int thr_left_speed = spd;
  int thr_right_speed = spd;
  if(thr_left_dir == 0)
    {
      thr_left_speed = -spd;
    }
  if(thr_right_dir == 0)
    {
      thr_right_speed = -spd;
    }
  thr_left.writeMicroseconds(int(MOTOR_STOP+(thr_left_speed*thr_left_k)));
  thr_right.writeMicroseconds(int(MOTOR_STOP+(thr_right_speed*thr_right_k)));
  }
}

void diving(int spd)
{
  if((spd<400)&&(spd>-400))
  {
    if(thr_vertical_dir == 0)
      {
        spd = -spd;
      }
     thr_vertical.writeMicroseconds(MOTOR_STOP+spd);
  }
}
