#include <Arduino.h>

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop()
{
  Serial.println("Led ON");
  digitalWrite(LED_BUILTIN,HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN,LOW);
  Serial.println("Led OFF");
  delay(100);

    }