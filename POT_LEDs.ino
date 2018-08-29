#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 7
#define DATA_PIN 2
CRGB leds[NUM_LEDS];          // Defines the array of leds

int potPin= A0;  //Declare potPin to be analog pin A0
int readValue;  // Use this variable to read Potentiometer
int writeValue; // Use this variable for writing to LED
 
void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(potPin, INPUT);  //set potPin to be an input
  Serial.begin(9600);      // turn on Serial Port
}
 
void loop() {
  
 readValue = analogRead(potPin);  //Read the voltage on the Potentiometer
 writeValue = (255./1023.) * readValue; //Calculate Write Value for LEDs
 Serial.print("You are writing a value of ");  //for debugging print your values
 Serial.println(readValue);
        leds[0] = CRGB(writeValue, writeValue, writeValue);
        leds[1] = CRGB(writeValue, writeValue, writeValue);
        leds[2] = CRGB(writeValue, writeValue, writeValue);
        leds[3] = CRGB(writeValue, writeValue, writeValue);
        leds[4] = CRGB(writeValue, writeValue, writeValue);
        leds[5] = CRGB(writeValue, writeValue, writeValue);
        leds[6] = CRGB(writeValue, writeValue, writeValue);
        FastLED.show();
 
}

