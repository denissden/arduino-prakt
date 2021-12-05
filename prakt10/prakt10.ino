/* Stepper Motor Control */

#include <Stepper.h>
const int stepsPerRevolution = 64;
Stepper motor(stepsPerRevolution, 8, 9, 10, 11);

int rPin = 51;
int gPin = 52;
int bPin = 53;

int button = 7;

int mode = 0;

void setup() {
   motor.setSpeed(80);
   pinMode(rPin, OUTPUT);
   pinMode(gPin, OUTPUT);
   pinMode(bPin, OUTPUT);
   pinMode(button, INPUT);
}

int r = 0;
int g = 0;
int b = 0;
int prevButton = 0;

void loop() {
  int currButton = digitalRead(7);
  if (currButton > prevButton) {
    changeMode();
  }
  prevButton = currButton;
  if (mode != 0)
    motor.step(1);
  digitalWrite(rPin, r);
  digitalWrite(gPin, g);
  digitalWrite(bPin, b);
}


void changeMode(){
  mode++;
  if (mode > 3) mode = 0;
  switch (mode){
    case 0:
      r = 0;
      g = 0;
      b = 0;
      break;
     case 1:
      motor.setSpeed(20);
      r = 0;
      g = 1;
      b = 0;
      break;
     case 2:
      motor.setSpeed(40);
      r = 1;
      g = 1;
      b = 0;
      break;
     case 3:
      motor.setSpeed(80);
      r = 1;
      g = 0;
      b = 0;
      break;
  }
}
