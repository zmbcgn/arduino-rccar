#include <RCSwitch.h>
// Define Inputpins of analog arcade joystick
int leftpin = 5;
int rightpin = 3;
int downpin = 4;
int uppin = 6;

// Create variables to store the values
int leftvalue = 0;
int rightvalue = 0;
int upvalue = 0;
int downvalue = 0;

// Initialize the sender
RCSwitch mySwitch = RCSwitch();

void setup() {
  mySwitch.enableTransmit(10);  // Sender is connected to pin10
  Serial.begin(9600);
// Setup pins as inputs
pinMode(leftpin,INPUT_PULLUP);
pinMode(rightpin,INPUT_PULLUP);
pinMode(uppin,INPUT_PULLUP);
pinMode(downpin,INPUT_PULLUP);

}
void loop() {
  leftvalue = digitalRead(leftpin);
  rightvalue = digitalRead(rightpin);
  upvalue = digitalRead(uppin);
  downvalue = digitalRead(downpin);
  if(leftvalue == LOW) {
     Serial.print(" Move Left ");
     mySwitch.send(1234, 24); // The 433mhz sender sends decimal „1234“
  }
  if(rightvalue == LOW) {
     Serial.print(" Move Right ");
     mySwitch.send(1235, 24); // The 433mhz sender sends decimal „1235“
  }
  if(upvalue == LOW) {
     Serial.print(" Move Up ");
     mySwitch.send(1236, 24); // The 433mhz sender sends decimal „1236“
  }
  if(downvalue == LOW) {
     Serial.print(" Move Down ");
     mySwitch.send(1237, 24); // The 433mhz sender sends decimal „1237“
  }
  /*else {
    Serial.print( "No Movement ");
    mySwitch.send(9999, 24);
   }
  */
 delay(50);
}  