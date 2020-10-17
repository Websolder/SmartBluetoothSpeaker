/**
 * @author  Yayi
 * @Website rtrobot.org
 * @Version 1.0.0
 * @Copyright  This code is public domain but you buy me a beer if you use
 * this and we meet someday (Beerware license).
 */
#include <Wire.h>
#include "PAJ7620.h"

#define PAJ7620_Delay 800
#define UP_FLAG 1
#define DOWN_FLAG 2
#define LEFT_FLAG 3
#define RIGHT_FLAG 4
#define CLOCKWISE_FLAG 5
#define COUNT_CLOCKWISE_FLAG 6
#define FORWARD_FLAG 7
#define BACKWARD_FLAG 8
#define WAVE_FLAG 9

void setup()
{
  uint8_t error = 0;

  //Serial initialize
  //Serial.begin(9600);
  //Serial.println("\r\nPAJ7620U2 TEST DEMO: Recognize 9 gestures.");

  //Serial1 initialize
  Serial1.begin(9600);
  //while(!Serial);
  //Serial.println("Arduino with HC-06-Master is ready");

  error = PAJ7620Init();      // initialize Paj7620 registers
  if (error) 
  {
   // Serial.print("INIT ERROR,CODE:");
    //Serial.println(error);
  }
  else
  {
   // Serial.println("INIT OK");
  }
  //Serial.println("Please input your gestures:\n");

 // pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  uint8_t data = 0;
  //digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)

  
  PAJ7620ReadReg(0x43, 1, &data);       // Read Bank_0_Reg_0x43/0x44 for gesture result.
  switch (data)               // When different gestures be detected, the variable 'data' will be set to different values by PAJ7620ReadReg(0x43, 1, &data).
  {
    case GES_RIGHT_FLAG:
      delay(PAJ7620_Delay);
      PAJ7620ReadReg(0x43, 1, &data);
      if(data == GES_FORWARD_FLAG) 
      {
        //Serial.println("Forward");
        //Serial1.println("Forward");
        Serial1.write(FORWARD_FLAG);
        delay(PAJ7620_Delay);
      }
      else if(data == GES_BACKWARD_FLAG) 
      {
        //Serial.println("Backward");
        Serial1.write(BACKWARD_FLAG);
        delay(PAJ7620_Delay);
      }
      else
      {
        //Serial.println("Right");     
        Serial1.write(RIGHT_FLAG); 
      }
    
      break;
      
    case GES_LEFT_FLAG: 
      delay(PAJ7620_Delay);
      PAJ7620ReadReg(0x43, 1, &data);
      if(data == GES_FORWARD_FLAG) 
      {
        //Serial.println("Forward");
        Serial1.write(FORWARD_FLAG);
        delay(PAJ7620_Delay);
      }
      else if(data == GES_BACKWARD_FLAG) 
      {
        //Serial.println("Backward");
        Serial1.write(BACKWARD_FLAG);
        delay(PAJ7620_Delay);
      }
      else
      {
         //Serial.println("Left");     
        Serial1.write(LEFT_FLAG);
      }
   
    break;
    
    case GES_UP_FLAG:
      delay(PAJ7620_Delay);
      PAJ7620ReadReg(0x43, 1, &data);
      if(data == GES_FORWARD_FLAG) 
      {
        //Serial.println("Forward");
        Serial1.write(FORWARD_FLAG);
        delay(PAJ7620_Delay);
      }
      else if(data == GES_BACKWARD_FLAG) 
      {
        //Serial.println("Backward");
        Serial1.write(BACKWARD_FLAG);
        delay(PAJ7620_Delay);
      }
      else
      {
        //Serial.println("Up");     
        Serial1.write(UP_FLAG); 
      }
  
      break;
      
    case GES_DOWN_FLAG:
      delay(PAJ7620_Delay);
      PAJ7620ReadReg(0x43, 1, &data);
      if(data == GES_FORWARD_FLAG) 
      {
        //Serial.println("Forward");
        Serial1.write(FORWARD_FLAG);
        delay(PAJ7620_Delay);
      }
      else if(data == GES_BACKWARD_FLAG) 
      {
        //Serial.println("Backward");
        Serial1.write(BACKWARD_FLAG);
        delay(PAJ7620_Delay);
      }
      else
      {
        //Serial.println("Down");    
        Serial1.write(DOWN_FLAG);
      }
       
    break;
    
    case GES_FORWARD_FLAG:
      //Serial.println("Forward");
      Serial1.write(FORWARD_FLAG);
      delay(PAJ7620_Delay);
    break;
      
    case GES_BACKWARD_FLAG:     
      //Serial.println("Backward");
      Serial1.write(BACKWARD_FLAG);
      delay(PAJ7620_Delay);
    break;
      
    case GES_CLOCKWISE_FLAG:
      //Serial.println("Clockwise");
      Serial1.write(CLOCKWISE_FLAG);
    break;
      
    case GES_COUNT_CLOCKWISE_FLAG:
      //Serial.println("anti-clockwise");
      Serial1.write(COUNT_CLOCKWISE_FLAG);
    break;  
      
    default:
      PAJ7620ReadReg(0x44, 1, &data);
      if (data == GES_WAVE_FLAG) 
      {
        //Serial.println("wave");
        Serial1.write(WAVE_FLAG);
      }

    break;
  }
  delay(500);
}
