/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 2.4.3 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.5.1 or later version;
     - for iOS 1.4.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// определение режима соединения и подключение библиотеки RemoteXY 

#include<Servo.h>

#define REMOTEXY_MODE__HARDSERIAL

#include <RemoteXY.h>

// настройки соединения 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 9600


// конфигурация интерфейса  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,2,0,11,0,32,0,10,13,0,
  67,4,60,15,29,9,2,26,11,1,
  0,19,12,12,12,2,31,49,0,1,
  0,21,35,12,12,2,31,48,0 };
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {

    // input variables
  uint8_t button_2; // =1 если кнопка нажата, иначе =0 
  uint8_t button_1; // =1 если кнопка нажата, иначе =0 

    // output variables
  char text_1[11];  // =строка UTF8 оканчивающаяся нулем 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define MOTOR_STOP 1500

Servo thr_left;
Servo thr_right;
Servo thr_vertical;

// изменить в соответствии со своей конфигурацией
//!!
int thr_left_dir = 1; //0-revers
int thr_right_dir = 1; //0-revers
int thr_vertical_dir = 1; // 0 -revers
//!!

// изменить в соответствии со своей конфигурацией
//!!
float thr_left_k = 0.7; // 0.1 ..1
float thr_right_k = 1; // 0.1..1
//!!

void move_linear(int spd);
void rotate(int spd);
void diving(int spd);

unsigned long time_out1 = 2000;
unsigned long time_out2 = 5000;
unsigned long time_out3 = 8000;

unsigned long timer_1,timer_2,timer_3;

int led_state = HIGH;

int counter;
int state = 0;
int action=0;

void setup() 
{
  RemoteXY_Init (); 

// изменить в соответствии со своей конфигурацией
//!!
  thr_left.attach(3); //horizontal
  thr_right.attach(5); //vertical
  thr_vertical.attach(6);  //horizontal
//!!
  
  thr_left.writeMicroseconds(MOTOR_STOP);
  thr_right.writeMicroseconds(MOTOR_STOP); 
  thr_vertical.writeMicroseconds(MOTOR_STOP);
  //delay(2000);
  
  timer_1 = millis();
  timer_2 = millis();
  timer_3 = millis();
}

void loop() 
{ 
  RemoteXY_Handler ();

  if((millis()-timer_1 > time_out1)&&(state==1))
    {
      //Serial.println("state 1");
      action = 1;
      timer_1 = millis();
      state = 2;
    }
  if((millis()-timer_2 > time_out2)&&(state==2))
    {
     // Serial.println("state 2");
      action = 2;
      timer_2 = millis();
      state = 3;
    }
  if((millis()-timer_2 > time_out2)&&(state==3))
    {
     // Serial.println("state 3");
      action = 0;
      timer_2 = millis();
      state = 0;
    }
  
  if (RemoteXY.button_2 == 1) 
     {
      timer_1 = millis();
      timer_2 = millis();
      timer_3 = millis();
      digitalWrite(13,HIGH);
      state = 1;
      }
   else if (RemoteXY.button_1 == 1) 
     {
      digitalWrite(13, LOW);
     // Serial.println("state 0");
      state = 0;
      action = 0;
      }
        //Serial.println(incomingChar);

    switch(action)
     {
      case 0:
        {
           move_linear(0);
           diving(0);
        //  Serial.println("action 0");
          break;
        }
      case 1:
        {
          move_linear(150);
          diving(250);
        //  Serial.println("action 1");
          break;
        }
      case 2:
        {
          rotate(120);
          diving(-250);
       //   Serial.println("action 2");
          break;
        }
     }
}

void move_linear(int spd)
{
  if((spd<300)&&(spd>-300))
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
  thr_left.writeMicroseconds(MOTOR_STOP+thr_left_speed);
  thr_right.writeMicroseconds(MOTOR_STOP+thr_right_speed);
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
  thr_left.writeMicroseconds(MOTOR_STOP+thr_left_speed);
  thr_right.writeMicroseconds(MOTOR_STOP-thr_right_speed);
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
