/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>
#include <Keyboard.h>

#define NUM_1 225
#define NUM_2 226
#define NUM_3 227
#define NUM_4 228
#define NUM_5 229
#define NUM_6 230
#define NUM_7 231
#define NUM_8 232

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(0, 1);
//   avoid using pins with LEDs attached

const int knobButtonPin = 2;
int knobButtonState;
int lastKnobButtonState;
unsigned long lastKnobDebounceTime = 0;

const int mainButtonPin = 7;
int mainButtonState;
int lastMainButtonState;
unsigned long lastMainDebounceTime = 0;

unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");

  pinMode(knobButtonPin, INPUT_PULLUP);
  pinMode(mainButtonPin, INPUT_PULLUP);

  Keyboard.begin();
}

long oldPosition  = -999;

void loop() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    if (newPosition > oldPosition || oldPosition - newPosition > 2000000) {
      for (int i = oldPosition; i < newPosition; i++) {
        Keyboard.press(NUM_1);
        Keyboard.release(NUM_1);
      }
    } else {
      for (int i = newPosition; i < oldPosition; i++) {
        Keyboard.press(NUM_2);
        Keyboard.release(NUM_2);
      }
    }
    oldPosition = newPosition;
    Serial.print("New encoder position: ");
    Serial.println(newPosition);
  }



  int knobButtonReading = digitalRead(knobButtonPin);
  if (knobButtonReading != lastKnobButtonState) {
    lastKnobDebounceTime = millis();
  }
  if ((millis() - lastKnobDebounceTime) > debounceDelay) {
    if (knobButtonReading != knobButtonState) {
      knobButtonState = knobButtonReading;
      if (knobButtonState == LOW) {
        Keyboard.press(NUM_3);
      } else {
        Keyboard.release(NUM_3);
      }
      Serial.print("debounced knob button is now ");
      Serial.println(knobButtonState);
    }
  }
  lastKnobButtonState = knobButtonReading;



  int mainButtonReading = digitalRead(mainButtonPin);
  if (mainButtonReading != lastMainButtonState) {
    lastMainDebounceTime = millis();
  }
  if ((millis() - lastMainDebounceTime) > debounceDelay) {
    if (mainButtonReading != mainButtonState) {
      mainButtonState = mainButtonReading;
      if (mainButtonState == LOW) {
        Keyboard.press(NUM_4);
      } else {
        Keyboard.release(NUM_4);
      }
      Serial.print("debounced main button is now ");
      Serial.println(mainButtonState);
    }
  }
  lastMainButtonState = mainButtonReading;
}
