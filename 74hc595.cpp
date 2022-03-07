# include <Arduino.h>

const uint8_t latchPin = 11;
const uint8_t clockpin = 9;
const uint8_t datapin = 12;
const int dt1 = 200;

byte led1 = 0b10101010;
byte led2 = 0b01010101;

void setup ()
{
  Serial.begin(9600);
  pinMode(latchPin,OUTPUT);
  pinMode(datapin,OUTPUT);
  pinMode(clockpin,OUTPUT);
}

void loop ()
{
  digitalWrite (latchPin,LOW);
  shiftOut(datapin,clockpin,LSBFIRST,led1);
  digitalWrite (latchPin,HIGH);
  delay(dt1);
  digitalWrite (latchPin,LOW);
  shiftOut(datapin,clockpin,LSBFIRST,led2);
  digitalWrite (latchPin,HIGH);
  delay(dt1);
}
