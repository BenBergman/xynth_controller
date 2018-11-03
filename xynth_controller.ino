/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>
#include <Joystick.h>

Joystick_ Joystick;

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





float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}




void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");

  pinMode(knobButtonPin, INPUT_PULLUP);
  pinMode(mainButtonPin, INPUT_PULLUP);

  Joystick.setXAxisRange(-32768, 32767);
  Joystick.setYAxisRange(-32768, 32767);
  Joystick.begin();
}

long oldPosition  = -999;

void loop() {
  unsigned long newPosition = myEnc.read() + 2000000;
  if (newPosition != oldPosition) {
    int rotation = newPosition % 80;

    // Map axis to follow a perfect circle from -1 to 1
    float xAxis = sin(rotation * 2.0 * PI / 80.0);
    float yAxis = -cos(rotation * 2.0 * PI / 80.0);

    // May axis to follow a perfect square from -1 to 1
    if (rotation < 10) {
      xAxis = mapFloat(rotation * 1.0, 0.0, 10.0, 0.0, 1.0);
      yAxis = -1.0;
    } else if (rotation < 30) {
      xAxis = 1.0;
      yAxis = mapFloat(rotation * 1.0, 10.0, 30.0, -1.0, 1.0);
    } else if (rotation < 50) {
      xAxis = mapFloat(rotation * 1.0, 30.0, 50.0, 1.0, -1.0);
      yAxis = 1.0;
    } else if (rotation < 70) {
      xAxis = -1.0;
      yAxis = mapFloat(rotation * 1.0, 50.0, 70.0, 1.0, -1.0);
    } else {
      xAxis = mapFloat(rotation * 1.0, 70.0, 80.0, -1.0, 0.0);
      yAxis = -1.0;
    }

    // Map axis to fill the axis range
    int16_t xMapped = xAxis * 32767.0;
    int16_t yMapped = yAxis * 32767.0;

    Joystick.setXAxis(xMapped);
    Joystick.setYAxis(yMapped);

    Serial.print("X axis: ");
    Serial.print(xAxis);
    Serial.print("   ");
    Serial.println(xMapped);
    Serial.print("Y axis: ");
    Serial.print(yAxis);
    Serial.print("   ");
    Serial.println(yMapped);

    oldPosition = newPosition;
    Serial.print("New encoder position: ");
    Serial.println(newPosition);

    Serial.print("New rotation: ");
    Serial.println(rotation);
  }



  int knobButtonReading = digitalRead(knobButtonPin);
  if (knobButtonReading != lastKnobButtonState) {
    lastKnobDebounceTime = millis();
  }
  if ((millis() - lastKnobDebounceTime) > debounceDelay) {
    if (knobButtonReading != knobButtonState) {
      knobButtonState = knobButtonReading;
      if (knobButtonState == LOW) {
        Joystick.pressButton(1);
      } else {
        Joystick.releaseButton(1);
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
        Joystick.pressButton(0);
      } else {
        Joystick.releaseButton(0);
      }
      Serial.print("debounced main button is now ");
      Serial.println(mainButtonState);
    }
  }
  lastMainButtonState = mainButtonReading;
}
