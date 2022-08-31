# include <Arduino.h>

void setup()
{
  Serial.begin(9600);
  pinMode(2,OUTPUT);
}

void loop()
{

  digitalWrite(2,1);
  Serial.println("led_ON");
  delay(100);
  digitalWrite(2,0);
  Serial.println("led_OFF");
  delay(100);
  
}