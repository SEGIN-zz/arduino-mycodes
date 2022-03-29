#include <Arduino.h>

int clk = 2;
int clkVal;
int dt = 3;
int dtVal;

void setup()
{
  Serial.begin(9600); // setting up SerialMonitor with a baudrate of 9600;
  pinMode(clk,INPUT);
  pinMode(dt,INPUT);

}

void loop()
{
  clkVal = digitalRead(clk); // reading the value of the encoder output pin clk,dt;
  dtVal = digitalRead(dt);
  
  Serial.print("clk = ");
  Serial.print(clkVal);
  Serial.print("  Dt = ");
  Serial.println(dtVal);

}