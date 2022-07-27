#include <Arduino.h>
int buttonpin=2;
int ledpin=3;
int buttonval;
int dt=100;

void setup ()
{
  Serial.begin(9600);
  pinMode(buttonpin,INPUT);
  pinMode(ledpin,OUTPUT);
}
void loop ()
{
  buttonval=digitalRead(buttonpin);
  Serial.print(buttonval);
  if (buttonval==1)
  {
    digitalWrite(ledpin,HIGH);
  }
  
  else
      {
        digitalWrite(ledpin,LOW);
      }
  
    
  
}
