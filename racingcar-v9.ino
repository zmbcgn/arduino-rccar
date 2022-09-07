#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <RCSwitch.h>

/*
  Racing Car
  Author: zmbcgn
  Date: 2021/12/24
  Version: 0.9
*/

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *moto_rearleft = AFMS.getMotor(1);
Adafruit_DCMotor *moto_frontleft = AFMS.getMotor(2);
Adafruit_DCMotor *moto_frontright = AFMS.getMotor(3);
Adafruit_DCMotor *moto_rearright = AFMS.getMotor(4);
RCSwitch remote = RCSwitch();

#define MOVE_LEFT 1234
#define MOVE_RIGHT 1235
#define MOVE_UP 1236
#define MOVE_DOWN 1237

void setup() {
  Serial.begin(115200);
  // Set all DC Motors to the same speed, so they the car is driving forward.
  AFMS.begin();
  set_speed();

  // 433 MHz Inputblock
  remote.enableReceive(0);  // INput is at Interrupt-Pin "0", which is PIN 2 at UNO
  Serial.println("ready");
}

void loop() {

  if (remote.available()) // If a code is received...
  {
    int value = remote.getReceivedValue(); // Input Data will be saved into var "value".
    Serial.print("Received ");
    Serial.println( value );
    drv_stop(); // Start with motors stopped

    switch (value) {

      case MOVE_UP:
        Serial.println("FWD");
        drv_forward();
        drv_stop();
        break;

      case MOVE_DOWN:
        Serial.println("REV");
        drv_backward();
        drv_stop();
        break;

      case MOVE_LEFT:
        Serial.println("LEFT");
        drv_turnleft();
        drv_stop();
        break;

      case MOVE_RIGHT:
        Serial.println("RIGHT");
        drv_turnright();
        drv_stop();
        break;

      default:
        Serial.println("Unknown Code");
    }
    remote.resetAvailable(); // Receiver reset
  }
}

void debug() {
  Serial.println("DEBUG");
}
void set_speed() {
  moto_rearleft->setSpeed(255);
  moto_frontleft->setSpeed(255);
  moto_frontright->setSpeed(255);
  moto_rearright->setSpeed(255);
}
void drv_forward() {
  set_speed();
  moto_rearleft->run(FORWARD);
  moto_frontleft->run(FORWARD);
  moto_frontright->run(FORWARD);
  moto_rearright->run(FORWARD);
}
void drv_backward() {
  set_speed();
  moto_rearleft->run(BACKWARD);
  moto_frontleft->run(BACKWARD);
  moto_frontright->run(BACKWARD);
  moto_rearright->run(BACKWARD);
}
void drv_turnleft() {
  set_speed();
  moto_rearleft->run(BACKWARD);
  moto_frontleft->run(BACKWARD);
  moto_frontright->run(FORWARD);
  moto_rearright->run(FORWARD);
}
void drv_turnright() {
  set_speed();
  moto_rearleft->run(FORWARD);
  moto_frontleft->run(FORWARD);
  moto_frontright->run(BACKWARD);
  moto_rearright->run(BACKWARD);
}
void drv_stop() {
  moto_rearleft->run(RELEASE);
  moto_frontleft->run(RELEASE);
  moto_rearright->run(RELEASE);
  moto_frontright->run(RELEASE);
}