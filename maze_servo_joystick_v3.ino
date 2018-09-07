// http://www.bajdi.com
// Pan/tilt kit controlled by joystick

#include <Servo.h> 
 
// Define servos
Servo panServo; 
Servo tiltServo; 

// Servo positions
byte panServoLeft = 10;
byte panServoCenter = 95;
byte panServoRight = 160;
byte panServoPos;
byte tiltServoUp = 160;
byte tiltServoCenter = 90;
byte tiltServoDown = 15;
byte tiltServoPos;

// Analog values of the joystick
int X;    // center = 519 up = 866, down = 77
int Y;    // center = 512 left = 996, right = 18 

#define runEvery(t) for (static typeof(t) _lasttime;(typeof(t))((typeof(t))millis() - _lasttime) > (t);_lasttime += (t))

void setup() 
{ 
  Serial.begin(9600);
  panServoPos = panServoCenter; 
  panServo.attach(7);  // (min=10/max=160) 
  panServo.write(panServoPos);
  
  tiltServoPos = tiltServoCenter;
  tiltServo.attach(6); // (min=15/max=160)
  tiltServo.write(tiltServoPos);
  delay(250);   // Give servos time to move to start position
} 
  
void loop() 
{ 
  runEvery(50)   // Runs every 20ms, slow down servo movement
  {
    X = analogRead(A0);    // read analog value from joystick X-axis
    Y = analogRead(A1);    // read analog value from joystick Y-axis
    
    
    if (X > 540 && tiltServoPos < tiltServoUp)
    {
      tiltServoPos += 1;    // move servo up
    }
    if (X < 500 && tiltServoPos > tiltServoDown)
    {
      tiltServoPos -= 1;    // move servo down
    }
    
    if (Y > 532 && panServoPos < panServoRight)
    {
      panServoPos += 1;      // move servo right
    }
    if (Y < 490 && panServoPos > panServoLeft)
    {
      panServoPos -= 1;      // move servo left
    }
    //move servos
    panServo.write(panServoPos);              
    tiltServo.write(tiltServoPos); 
  }
  
  // Serial printing of variables for debugging
  runEvery(500){             
    Serial.print("X = ");
    Serial.println(X);
    Serial.print("Y = ");
    Serial.println(Y);
    Serial.print("tiltServoPos = ");
    Serial.println(tiltServoPos);
    Serial.print("panServoPos = ");
    Serial.println(panServoPos);
  }
} 
