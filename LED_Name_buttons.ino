// Radio Buttons!
const int led1Pin =  3;    // LED pin number
const int button1 =  2;
const int led2Pin =  5; 
const int button2 =  4;
const int led3Pin =  6;
const int button3 =  7;
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
  pinMode(led1Pin, OUTPUT);      
  pinMode(button1, INPUT); 
  pinMode(led2Pin, OUTPUT);      
  pinMode(button2, INPUT);      
  pinMode(led3Pin, OUTPUT);      
  pinMode(button3, INPUT);       
  digitalWrite (led1Pin, LOW);
  digitalWrite (led2Pin, LOW);
  digitalWrite (led3Pin, LOW);
}

void loop() {
  // Select LED if button debounced
  if (butndown(digitalRead(button1), &bcount1, &bstate1, 10UL )) {
    digitalWrite (led1Pin, HIGH);
    digitalWrite (led2Pin, LOW);
    digitalWrite (led3Pin, LOW);
    delay(500);
  } 
  // Select LED if button debounced
  if (butndown(digitalRead(button2), &bcount2, &bstate2, 10UL )) {
    digitalWrite (led1Pin, LOW);
    digitalWrite (led2Pin, HIGH);
    digitalWrite (led3Pin, LOW);
    delay(500);
  } 
  // Select LED if button debounced
  if (butndown(digitalRead(button3), &bcount3, &bstate3, 10UL )) {
    digitalWrite (led1Pin, LOW);
    digitalWrite (led2Pin, LOW);
    digitalWrite (led3Pin, HIGH);
    delay(500);
  }
}
