# include<Arduino.h>

const uint8_t trigpin = 12;
const uint8_t echopin = 13;
long pingTravelTime;

void setup ()
{
  Serial.begin(9600);
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
}
void loop ()
{
  digitalWrite(trigpin,LOW);
  delayMicroseconds(10);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  pingTravelTime = pulseIn(echopin,HIGH);
  delay(50);
  Serial.println(pingTravelTime);
}
