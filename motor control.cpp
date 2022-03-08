#include<Arduino.h>

int potpin=A0;
int motorpin=3;
int potval;
int dt=100;
int v0;

void setup()
{
  Serial.begin(9600);
  pinMode(potpin,INPUT);
  pinMode(motorpin,OUTPUT);
}

void loop()
{
  potval=analogRead(potpin);
  v0=(255./1023.)*potval;
  analogWrite(motorpin,v0);
  Serial.println(v0);
}
