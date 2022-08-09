/*
question :

Prepare an embedded code that blinks 2 LEDS.
LED 1 should blink every 2 seconds.
LED 2 should blink every 3 seconds.

You can use any embedded language of your choice.


Ans :
  using arduino uno 
  using platform.io

  gitHub link -> https://github.com/segin-GH/Embedded-codes/blob/main/arduino_codes/millis_delay/src/main.cpp


thinkercad sim link ->  https://www.tinkercad.com/things/9IwXHECjs7R?sharecode=LW6NKhy1WuINhVloYchyXTPxl5EDA9dA6u6QEysj9Ww
*/


# include <Arduino.h>

int redLedPin = 2;
bool redledState = LOW;
int greeLedPin = 3;
bool greenledState = LOW;

int delayOne = 2000;
int delayTwo = 3000;

unsigned long prev_time = 0;
unsigned long prev_time2 = 0;



void setup()
{
  pinMode(redLedPin,OUTPUT);
  pinMode(greeLedPin,OUTPUT);
  Serial.begin(9600);

}

void loop ()
{

  unsigned long curr_time = millis();

  if(curr_time - prev_time >= delayOne)
  {
    prev_time += delayOne;
    
    if (redledState == LOW)
    {
      redledState = HIGH;
    }
    else
    {
      redledState = LOW;
    }
  }


  unsigned  curr_time2 = millis();

  if(curr_time2 - prev_time2 >= delayTwo)
  {
    prev_time2 += delayTwo;
    
    if (greenledState == LOW)
    {
      greenledState = HIGH;
    }
    else
    {
      greenledState = LOW;
    }
  }

  digitalWrite(redLedPin,redledState);
  digitalWrite(greeLedPin,greenledState);


}