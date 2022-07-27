#include <Arduino.h>
#include<LiquidCrystal.h>
#include<Wire.h>

const byte rs = 7;         //  lcd
const byte en = 8; 
const byte d4 = 9;
const byte d5 = 10;
const byte d6 = 11;
const byte d7 = 12;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

const byte potpin = A0;    // poteniometer
int potval;
byte opration = 0;

const byte buttonpin = A1;      // pushbutton
byte newbutt ;
byte state  = 0;

unsigned long prevtime = 0;
const long interval = 80;  // using millis as delay
byte dymode = 0;

void setup ()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(potpin,INPUT);
  pinMode(buttonpin,INPUT);
  
}
void loop ()
{
  lcd.clear();
  newbutt = digitalRead(buttonpin);
  unsigned long currtime = millis();      // miliis
  if (currtime - prevtime >= interval)
  {
    prevtime = currtime; 
    if (dymode == 0)            // milli mode switching
    { 
      if(newbutt == LOW)             // button
      {
        state++;
        dymode = 1;
      }
      
    }
    else
    {
      if (state > 10)
      {
          state = 0;
      }
      dymode = 0;
    }
  
  }
 
 if ( state == 0 )
 {
  lcd.setCursor(0,0);
  lcd.print("select operation");
  
  potval = analogRead(potpin);
  int v2 = (3./1023.)*potval;
  if (v2 == 0)
   {
      lcd.setCursor(15,1);
      lcd.rightToLeft();
      lcd.print(" + ");
      opration = 1;
   }
   else if(v2 == 1)
   {
    lcd.setCursor(15,1);
     lcd.rightToLeft();
     lcd.print(" - ");
     opration = 2;
   }
   else if(v2 == 2)
   {
     lcd.setCursor(15,1);
     lcd.rightToLeft();
     lcd.print (" * ");
     opration = 3;
   }
   else if (v2 == 3)
   {
     lcd.setCursor(15,1);
     lcd.rightToLeft();
     lcd.print(" / ");
     opration = 4;
   }

 }

 if (state == 1 && opration == 1)
 {
   lcd.clear();
   unsigned long x;
   unsigned long y;
   unsigned long x1;
   unsigned long y;
   Serial.println("X =");
   lcd.print("X =");
   while(Serial.available() == 0)
   {
    //
   }
   x = Serial.parseInt();
   
   Serial.println(x);
   if (x != 0)
   {
     lcd.setCursor(0,1);
     lcd.print(x);
   }
   delay(1000);

 }   
}






