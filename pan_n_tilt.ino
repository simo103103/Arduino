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
const int pitchHm = 138;   //set so pitch direction is level
const int rollHm = 125;    //set so roll direction is level
int delayVal=50;

void setup()  //setup runs one time
{
  pitchServo.attach(6);  //attach servos to pins
  rollServo.attach(7);
  
  pitchServo.slowmove(pitchHm, svsp);  //Home servos to start
  rollServo.slowmove(rollHm, svsp);
}

void loop() //loop repeats forever
{   
  for(int i=0; i<30; i++) {
        pitchServo.slowmove(pitchHm+i, svsp);
        rollServo.slowmove(rollHm+i, svsp);
        delay(delayVal);
        }
  for(int i=0; i<30; i++) {
        pitchServo.slowmove(pitchHm-i, svsp);
        rollServo.slowmove(rollHm-i, svsp);
        delay(delayVal);
        }
  for(int i=0; i<30; i++) {
        pitchServo.slowmove(pitchHm+i, svsp);
        rollServo.slowmove(rollHm-i, svsp);
        delay(delayVal);
        }
   for(int i=0; i<30; i++) {
        pitchServo.slowmove(pitchHm-i, svsp);
        rollServo.slowmove(rollHm+i, svsp);
        delay(delayVal);
        }
   
}
