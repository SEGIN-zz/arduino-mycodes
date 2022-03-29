# include <Arduino.h>

int clk = 2;
int dt = 3;

int counter = 0;
int curent_State_CLK;
int previous_state_CLK;
String encdir;

void setup()
{
  Serial.begin(9600);
  pinMode(clk,INPUT);
  pinMode(dt,INPUT);

  previous_state_CLK = digitalRead(clk);
}

void loop()
{
  
  curent_State_CLK = digitalRead(clk);
  
  if (curent_State_CLK != previous_state_CLK)
  {
    if (digitalRead(dt) != curent_State_CLK)
    {
      counter--;
      encdir = "ccw";
    }
    else
    {
      counter++;
      encdir = "cw";
    }
    Serial.print("Direction = ");
    Serial.print(encdir);
    Serial.print("  Value = ");
    Serial.println(counter);

  }

}
