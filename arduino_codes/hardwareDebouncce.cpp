# include <Arduino.h>

void endLimitOneAttained();
void endLimitTwoAttained();



int count = 0;
int count2 =0;

void setup()
{
  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  attachInterrupt(0,endLimitOneAttained,FALLING);
  attachInterrupt(1,endLimitTwoAttained,FALLING);

}

void loop()
{
//
}

void endLimitOneAttained()
{
  count = count + 1;
  Serial.println(count);
}

void endLimitTwoAttained()
{
  count2 = count2 +1;
  Serial.println(count2);
}
