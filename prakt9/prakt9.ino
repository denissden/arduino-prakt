/* Stepper Motor Control */

#include <Stepper.h>
const int stepsPerRevolution = 64;
Stepper motor(stepsPerRevolution, 8, 9, 10, 11);

int rPin = 51;
int gPin = 52;
int bPin = 53;

int soundPin = 7;

int pot = A0;

int mode = 0;

void setup() {
   motor.setSpeed(80);
   pinMode(rPin, OUTPUT);
   pinMode(gPin, OUTPUT);
   pinMode(bPin, OUTPUT);
   pinMode(pot, INPUT);
}

void loop() {
  int val = analogRead(pot);
  if (val > 500){
    tone(soundPin, 500);
    digitalWrite(bPin, 0);
    digitalWrite(rPin, 1);
    delay(200);
    digitalWrite(rPin, 0);
    delay(200);
  }
  else {
    noTone(soundPin);
    digitalWrite(bPin, 1);
    delay(100);
  }
}
