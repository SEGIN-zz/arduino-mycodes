# include <Arduino.h>

int LED=13;
int dt=500;

void setup ()
{
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
}
void loop ()
{
  digitalWrite(LED,HIGH);
  Serial.println("LED ON");
  delay(dt);
  digitalWrite(LED,LOW);
  Serial.println("LED OFF");
  delay(dt);

}