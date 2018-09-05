/*
This sketch centers your maze servos on the maze BT control project

 * pitch servo pin 6 group
 * roll servo pin 7 group
 
Written by The Bridgeville Delaware Public Library Teen Imagineering Club
This code is in the public domain 
 */

#include <VarSpeedServo.h>  //include the VarSpeedServo library

VarSpeedServo pitchServo;   //create VarSpeedServo objects for pitch and roll
VarSpeedServo rollServo;

const int svsp = 20;   //speed setting for VarSpeedServo SlowMove
const int pitchHm = 117;   //set so pitch direction is level
const int rollHm = 83;    //set so roll direction is level
const int VRx = 0; // Connect to Analog Pin 0
const int VRy = 1; // Connect to Analog Pin 1
const int SW = 4; // Connect to Digital Pin 4
int refreshTime = 600;  // make this smaller to make servo move faster
const int tiltAmt = 15;   //set how much it tilts in each direction

void setup()  //setup runs one time
{
  pitchServo.attach(6);  //attach servos to pins
  rollServo.attach(7);
  
  pitchServo.slowmove(pitchHm, svsp);  //Home servos to start
  rollServo.slowmove(rollHm, svsp);
  pinMode(SW, INPUT);
  digitalWrite(SW, HIGH);
  Serial.begin(9600);
}

void loop() //loop repeats forever
{   
   int joyReadx = analogRead(VRx);
   int joyReady = analogRead(VRy);
  Serial.print("Y: ");
  Serial.print(joyReady);
  Serial.print(" X: ");
  Serial.println(joyReadx);

  if (joyReadx < 800 && joyReadx > 300 && joyReady < 800 && joyReady > 300) {
      pitchServo.slowmove(pitchHm, svsp);  //Home servos to start
      rollServo.slowmove(rollHm, svsp);
      pinMode(SW, INPUT);
      digitalWrite(SW, HIGH);
  } else if (joyReadx > 800 && joyReady > 800) {
      pitchServo.slowmove(pitchHm+tiltAmt, svsp);  //Home servos to start
      rollServo.slowmove(rollHm+tiltAmt, svsp);
      pinMode(SW, INPUT);
      digitalWrite(SW, HIGH);
  
  } else if (joyReadx < 300 && joyReady > 800) {
      pitchServo.slowmove(pitchHm-tiltAmt, svsp);  //Home servos to start
      rollServo.slowmove(rollHm+tiltAmt, svsp);
      pinMode(SW, INPUT);
      digitalWrite(SW, HIGH);
  } else if (joyReadx < 300 && joyReady < 300) {
      pitchServo.slowmove(pitchHm-tiltAmt, svsp);  //Home servos to start
      rollServo.slowmove(rollHm-tiltAmt, svsp);
      pinMode(SW, INPUT);
      digitalWrite(SW, HIGH);
  } else if (joyReadx > 800 && joyReady < 300) {
      pitchServo.slowmove(pitchHm+tiltAmt, svsp);  //Home servos to start
      rollServo.slowmove(rollHm-tiltAmt, svsp);
      pinMode(SW, INPUT);
      digitalWrite(SW, HIGH);

  } else if (joyReadx < 300) {
      pitchServo.slowmove(pitchHm-tiltAmt, svsp);  //Home servos to start
      rollServo.slowmove(rollHm, svsp);
      pinMode(SW, INPUT);
      digitalWrite(SW, HIGH);

  } else if (joyReadx > 800 ) {
      pitchServo.slowmove(pitchHm+tiltAmt, svsp);  //Home servos to start
      rollServo.slowmove(rollHm, svsp);
      pinMode(SW, INPUT);
      digitalWrite(SW, HIGH);


      
  } else if (joyReady > 800) {
      pitchServo.slowmove(pitchHm, svsp);  //Home servos to start
      rollServo.slowmove(rollHm+tiltAmt, svsp);
      pinMode(SW, INPUT);
      digitalWrite(SW, HIGH);
  } else if (joyReady < 300) {
      pitchServo.slowmove(pitchHm, svsp);  //Home servos to start
      rollServo.slowmove(rollHm-tiltAmt, svsp);
      pinMode(SW, INPUT);
      digitalWrite(SW, HIGH);
  }
  delay(refreshTime);
}
