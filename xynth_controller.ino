/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

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
}

long oldPosition  = -999;

void loop() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
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
      Serial.print("debounced main button is now ");
      Serial.println(mainButtonState);
    }
  }
  lastMainButtonState = mainButtonReading;
}
