#include "FastLED.h"

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    7
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    7
CRGB leds[NUM_LEDS];

unsigned long previousMillis = 0;        // will store last time LED was updated
long OnTime = 250;           // milliseconds of on-time
long OffTime = 75000;          // milliseconds of off-time

// Radio Buttons!
int ButtonVal = 0;
float BRIGHTNESS = 255;
#define FRAMES_PER_SECOND  120

bool gReverseDirection = false;
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

void setup() 
{
   delay(3000); // 3 second delay for recovery
  // set the digital pin as output:
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(9600);    
}

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns


void loop()
{ 
  // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();

  if (butndown(digitalRead(button1), &bcount1, &bstate1, 10UL )) {
     ButtonVal=1;
  }
  if (butndown(digitalRead(button2), &bcount2, &bstate2, 10UL )) {
     ButtonVal=2;
  }

  if (butndown(digitalRead(button3), &bcount3, &bstate3, 10UL )) {
     ButtonVal=3;
  }

   if ((ButtonVal == 1) && (currentMillis - previousMillis >= OnTime))
        {
          leds[0] = CRGB(255,255,255);
          leds[1] = CRGB(255,255,255);
          leds[2] = CRGB(255,255,255);
          leds[3] = CRGB(255,255,255);
          leds[4] = CRGB(255,255,255);
          leds[5] = CRGB(255,255,255);
          leds[6] = CRGB(255,255,255);
          if (BRIGHTNESS >=20) {
            BRIGHTNESS=BRIGHTNESS-0.1;
          }
          FastLED.setBrightness(BRIGHTNESS);
          Serial.println(BRIGHTNESS);
         FastLED.show();
          previousMillis = currentMillis;  // Remember the time
          
        } else if (ButtonVal == 3){
          BRIGHTNESS=255;
          // Call the current pattern function once, updating the 'leds' array
            gPatterns[gCurrentPatternNumber]();
          
            // send the 'leds' array out to the actual LED strip
            FastLED.show();  
            // insert a delay to keep the framerate modest
            FastLED.delay(1000/FRAMES_PER_SECOND); 
          
            // do some periodic updates
            EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
            EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
          
        } else if (ButtonVal == 2){
            Fire2012(); // run simulation frame
            FastLED.show(); // display this frame
            FastLED.delay(1000 / FRAMES_PER_SECOND);
        }     
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

#define SPARKING 120
#define COOLING  55

void Fire2012()
{
// Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
      CRGB color = HeatColor( heat[j]);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
}
