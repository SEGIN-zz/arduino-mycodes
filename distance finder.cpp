#include<Arduino.h>
#include<LiquidCrystal.h>
#include<Wire.h>

const int dt0 = 1000;
const uint8_t rs = 6;
const uint8_t en = 7;
const uint8_t d4 = 8;
const uint8_t d5 = 9;
const uint8_t d6 = 10;
const uint8_t d7 = 11;
LiquidCrystal  lcd (rs, en, d4, d5, d6, d7);

const uint8_t trigerpin = 2;
const uint8_t echopin = 3;
const uint8_t dt1 = 10;
const uint8_t dt2 = 25;
int  ptt;
void setup ()
{
  pinMode(trigerpin,OUTPUT);
  pinMode(echopin,INPUT);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("distance meter");
  delay(dt0);
  lcd.clear();
  Serial.begin(9600);
}
void loop ()
{
  digitalWrite(trigerpin,LOW);
  delayMicroseconds(dt1);
  digitalWrite(trigerpin,HIGH);
  delayMicroseconds(dt1);
  digitalWrite(trigerpin,LOW);
  ptt = pulseIn(echopin,HIGH);
  int d = ( ptt / 2)*0.0343;
  delay(100);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(d);
  lcd.print("cm");
}
