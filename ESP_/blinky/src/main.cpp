
/*
TODO
1. Set up LEDs on pin GPIO18 and GPIO5 using the wowki simulator
2. Turn pins GPIO18 and GPIO5 into PWM pins
3. Gradually Increase brightness on these LEDs from zero to max voltage over 5 seconds (20% brightness after 1 second, 40% brightness after 2 seconds, and so on).
 Both pins should have equal brightness at all times
4. Turn off LEDs for 2 seconds
5. Increase to full brightness over 1 second (50% brightness after 0.5 second)
6. Repeat steps 3-5 four times
7. Permanently turn off
(https://wokwi.com/projects/new/esp32)

*/

#include <Arduino.h>

const int ledOne = 18;
const int ledTwo = 5;
const long interval = 100;
int ledstate = LOW;
unsigned long prevtime = 0;
int numTimesLooped = 0;
double timeCount = 1;

void ledlightingSequence();


void setup()
{
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  while (numTimesLooped < 3) 
  {
    ledlightingSequence();
  }
}

void ledlightingSequence()
{
  unsigned long currtime = millis();
  if (currtime - prevtime >= interval)
  {
    prevtime += interval;
    timeCount = timeCount + .10;
  }

  if (timeCount <= 5)
  {
    int mapVal = map(timeCount, 0, 5, 0, 255);
    analogWrite(ledOne, mapVal);
  }
  if (timeCount > 5 && timeCount < 7)
  {
    analogWrite(ledOne, LOW);
  }

  if (timeCount > 7 && timeCount < 8)
  {
    int mapVal = map(timeCount, 0, 1, 0, 255);
    analogWrite(ledOne, mapVal);
  }

  Serial.println(timeCount);

  if (timeCount > 8)
  {
    timeCount = 0;
    numTimesLooped++;
  }

  
}