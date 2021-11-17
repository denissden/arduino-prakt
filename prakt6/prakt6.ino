#include <SPI.h>

int dataPin = 3;    // к выводу 14 регистра DS
int latchPin = 2;  // к выводу 12 регистра (ST_CP)
int clockPin = 1;  // к выводу 11 регистра (SH_CP)


byte leds = 0b00011011;
byte number = 0;

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(38400);
  Serial.setTimeout(100);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
}


byte leds2 = 0;

void loop() 
{
  int input = Serial.parseInt();
  if (input > 0 && input < 8){
    leds = 0;
    bitSet(leds, input - 1);
  }
  digitalWrite(latchPin, LOW);
  SPI.transfer(leds);
  digitalWrite(latchPin, HIGH);
}

void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
