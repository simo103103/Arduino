#include "OneWire.h"
#include "DallasTemperature.h"
 #include "FastLED.h"

  // How many leds in your strip?
#define NUM_LEDS 7
#define DATA_PIN 2

CRGB leds[NUM_LEDS];          // Defines the array of leds
const int delayVal =  200;    // Define the delay 1000=1sec

#define ONE_WIRE_BUS 5

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

 float Celcius=0;
 float Fahrenheit=0;
void setup(void)
{
  
  Serial.begin(9600);
  sensors.begin();
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop(void)
{ 
  sensors.requestTemperatures(); 
  Celcius=sensors.getTempCByIndex(0);
  Fahrenheit=sensors.toFahrenheit(Celcius);
  Serial.print(" C  ");
  Serial.print(Celcius);
  Serial.print(" F  ");
  Serial.println(Fahrenheit);
  delay(1000);
  if (Celcius >29) {
        // Turn the LED on, then pause
        leds[0] = CRGB::Green;
        leds[1] = CRGB::Green;
        leds[2] = CRGB::Blue;
        leds[3] = CRGB::Blue;
        leds[4] = CRGB::Red;
        leds[5] = CRGB::Red;
        leds[6] = CRGB(50, 100, 150);
     
        FastLED.show();
        delay(delayVal);
  } else {
        // Now turn the LED off, then pause
        leds[0] = CRGB::Black;
        leds[1] = CRGB::Black;
        leds[2] = CRGB::Black;
        leds[3] = CRGB::Black;
        leds[4] = CRGB::Black;
        leds[5] = CRGB::Black;
        leds[6] = CRGB::Black;
        FastLED.show();
        delay(delayVal);
  }
}
