#include <SPI.h>

//int dataPin = 3;    // к выводу 14 регистра DS
int latchPin = 2;  // к выводу 12 регистра (ST_CP)
//int clockPin = 1;  // к выводу 11 регистра (SH_CP)


byte leds = 0b11111111;
byte number = 0;

byte numbers[10] = { 
      //.gfedcba
      0b01011111,
      0b00000110,
      0b00111011,
      0b00101111,
      0b01100110,
      0b01101101,
      0b01111101,
      0b00000111,
      0b01111111,
      0b01101111,
  };

void setup() 
{
  pinMode(latchPin, OUTPUT);
  Serial.begin(38400);
  Serial.setTimeout(100);
  // SPI uses pin 51 as data on MEGA
  // and pin 52 as clock
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
}


byte leds2 = 0;

void loop() 
{
  int input = Serial.parseInt();
  if (input > 0 && input <= 9)
    timer(input);
//  if (input > 0 && input <= 9)
//    leds = numbers[input];
//  else if (input == 10)
//    leds = numbers[0];
//  else if (input == -1)
//    leds = 0;
  draw();
}

void timer(int time) {  
  leds = 0b10000000;
  draw();
  delay(1000);
  leds = 0b00000000;
  draw();
  delay(1000);
  for (int i = time; i >= 0; i--){
    leds = numbers[i];
    draw();
    delay(1000);
  }
  leds = 0;
  draw();
}

void draw(){
  digitalWrite(latchPin, LOW);
  SPI.transfer(leds);
  digitalWrite(latchPin, HIGH);
}
  
