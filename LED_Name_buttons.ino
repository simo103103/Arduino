#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 12 
#define DATA_PIN 7

// Define the array of leds
CRGB leds[NUM_LEDS];

// Radio Buttons!
const int button1 =  2;
const int button2 =  4;
const int button3 =  6;
char bstate1 = 0;
char bstate2 = 0;
char bstate3 = 0;
unsigned long bcount1 = 0; // button debounce timer.  Replicate as necessary.
unsigned long bcount2 = 0;
unsigned long bcount3 = 0;


// Have we completed the specified interval since last confirmed event?
// "marker" chooses which counter to check
// Routines by Paul__B of Arduino Forum
boolean timeout(unsigned long *marker, unsigned long interval) {
  if (millis() - *marker >= interval) { 
    *marker += interval;    // move on ready for next interval
    return true;       
  } 
  else return false;
}

// Deal with a button read; true if button pressed and debounced is a new event
// Uses reading of button input, debounce store, state store and debounce interval.
// Routines by Paul__B of Arduino Forum
boolean butndown(char button, unsigned long *marker, char *butnstate, unsigned long interval) {
  switch (*butnstate) {               // Odd states if was pressed, >= 2 if debounce in progress
  case 0: // Button up so far, 
    if (button == HIGH) return false; // Nothing happening!
    else { 
      *butnstate = 2;                 // record that is now pressed
      *marker = millis();             // note when was pressed
      return false;                   // and move on
    }

  case 1: // Button down so far, 
    if (button == LOW) return false; // Nothing happening!
    else { 
      *butnstate = 3;                 // record that is now released
      *marker = millis();             // note when was released
      return false;                   // and move on
    }

  case 2: // Button was up, now down.
    if (button == HIGH) {
      *butnstate = 0;                 // no, not debounced; revert the state
      return false;                   // False alarm!
    }
    else { 
      if (millis() - *marker >= interval) {
        *butnstate = 1;               // jackpot!  update the state
        return true;                  // because we have the desired event!
      }
      else 
        return false;                 // not done yet; just move on
    }

  case 3: // Button was down, now up.
    if (button == LOW) {
      *butnstate = 1;                 // no, not debounced; revert the state
      return false;                   // False alarm!
    }
    else { 
      if (millis() - *marker >= interval) {
        *butnstate = 0;               // Debounced; update the state
        return false;                 // but it is not the event we want
      }
      else 
        return false;                 // not done yet; just move on
    }
  default:                            // Error; recover anyway
    {  
      *butnstate = 0;
      return false;                   // Definitely false!
    }
  }
}

void setup() {     
  pinMode(button1, INPUT);      
  pinMode(button2, INPUT);       
  pinMode(button3, INPUT);       
  //FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
  FastLED.setBrightness(255);
  Serial.begin(57600);
}

void loop() {
  // Select LED if button debounced
  if (butndown(digitalRead(button1), &bcount1, &bstate1, 10UL )) {
    leds[0] = CRGB(0,255,0);
    leds[1] = CRGB(0,250,0);
    leds[2] = CRGB(255,255,255);
    leds[3] = CRGB(255,255,255);
    leds[4] = CRGB(255,110,0);
    leds[5] = CRGB(255,0,0);
   FastLED.show();
    delay(500);
  } 
  // Select LED if button debounced
  if (butndown(digitalRead(button2), &bcount2, &bstate2, 10UL )) {
    leds[0] = CRGB(0,255,0);
    leds[1] = CRGB(0,250,0);
    leds[2] = CRGB(255,255,0);
    leds[3] = CRGB(255,110,0);
    leds[4] = CRGB(255,110,0);
    leds[5] = CRGB(255,0,0);
    Serial.println("Button 1 ");
   FastLED.show();
    delay(500);
  } 
  // Select LED if button debounced
  if (butndown(digitalRead(button3), &bcount3, &bstate3, 10UL )) {
    leds[0] = CRGB(0,255,0);
    leds[1] = CRGB(0,250,0);
    leds[2] = CRGB(255,255,0);
    leds[3] = CRGB(255,110,0);
    leds[4] = CRGB(255,110,0);
    leds[5] = CRGB(255,0,0);
    Serial.println("Button 2 ");
   FastLED.show();
    delay(500);
  }
}
