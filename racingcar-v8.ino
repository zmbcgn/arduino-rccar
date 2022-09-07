#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <RCSwitch.h>

/*
Racing Car 
Author: Philipp Maihöfer
Date: 2021/12/14
Version: 0.8
*/

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *moto_rearleft = AFMS.getMotor(1);
Adafruit_DCMotor *moto_frontleft = AFMS.getMotor(2);
Adafruit_DCMotor *moto_frontright = AFMS.getMotor(3);
Adafruit_DCMotor *moto_rearright = AFMS.getMotor(4);
RCSwitch remote = RCSwitch();

void setup() {
// Set all DC Motors to the same speed, so they the car is driving forward. 
AFMS.begin();
set_speednormal();

// 433 MHz Inputblock
 Serial.begin(9600);
 remote.enableReceive(0);  // INput is at Interrupt-Pin "0", which is PIN 2 at UNO
}

void loop() {
  
  if (remote.available()) // If a code is received...
  {
    long value = remote.getReceivedValue(); // Input Data will be saved into var "value".
    if (value == 0) // If input is "0", we will print "unknown code" to serial
    {
      Serial.println("Unknown Code");
    } 
    else if (value == 1236) // If the input code is the value "1234".
      {
      Serial.print("Received inside elseif: ");
      Serial.println( value );
      drv_forward();
      delay(2000);
      }
    else if (value == 1237)
    {
      Serial.print("Received inside second elseif: ");
      Serial.println( value );
      drv_backward();
      delay(2000);
      debug(10);
    }
     else if (value == 1235)
      {
      Serial.print("Received inside third elseif: ");
      Serial.println( value );
      drv_turnright();
      delay(2000);
    }
     else if (value == 1234)
    {
      Serial.print("Received inside forth elseif: ");
      Serial.println( value );
      drv_turnleft();
      delay(2000);
    }
     else 
      {
      Serial.print("Received inside else: ");
      Serial.println( value );
      delay(2000);
      drv_stop();
      debug(999);
    }
  remote.resetAvailable(); // Receiver reset
  debug(99);
  drv_stop();
  }
}

void debug(int debugcode) {
  Serial.print("DEBUG: ");
  Serial.println(debugcode);
}
void set_speednormal() {
  moto_rearleft->setSpeed(200);
  moto_frontleft->setSpeed(200);
  moto_frontright->setSpeed(200);
  moto_rearright->setSpeed(200);
}
void drv_forward() {
  set_speednormal();
  moto_rearleft->run(FORWARD);
  moto_frontleft->run(FORWARD);
  moto_frontright->run(FORWARD);
  moto_rearright->run(FORWARD);
}
void drv_backward() {
  set_speednormal();
  moto_rearleft->run(BACKWARD);
  moto_frontleft->run(BACKWARD);
  moto_frontright->run(BACKWARD);
  moto_rearright->run(BACKWARD);
 }
void drv_turnleft() {
  set_speednormal();
  moto_frontleft->setSpeed(40);
  moto_rearleft->run(FORWARD);
  moto_frontleft->run(FORWARD);
  moto_frontright->run(FORWARD);
  moto_rearright->run(FORWARD);
}
void drv_turnright() {
  set_speednormal();
  moto_frontright->setSpeed(40);
  moto_rearleft->run(FORWARD);
  moto_frontleft->run(FORWARD);
  moto_frontright->run(FORWARD);
  moto_rearright->run(FORWARD);
}  
void drv_stop() {
  moto_frontright->run(RELEASE);
  moto_frontleft->run(RELEASE);
  moto_rearright->run(RELEASE);
  moto_rearleft->run(RELEASE);
}