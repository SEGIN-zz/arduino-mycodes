
# include<Arduino.h>

const int redled = 2;
const long interval = 100;
int ledstate = LOW;
unsigned long prevtime = 0;

void setup()
{
  pinMode(redled,OUTPUT);
  Serial.begin(9600);
}

void loop ()
{
  unsigned long currtime = millis();

  if (currtime - prevtime >= interval)
  {
    prevtime = currtime;
    Serial.print("curr:  ");
     Serial.print(currtime);
      Serial.print("   prev:  ");
       Serial.println(prevtime);

    if (ledstate == LOW) 
    {
      ledstate = HIGH;
    } 
    else 
    {
      ledstate = LOW;
    }
    digitalWrite(redled,ledstate);
  }
}



