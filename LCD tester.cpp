# include <Arduino.h>
# include <LiquidCrystal.h>


const uint8_t rs = 8;
const uint8_t en = 9;
const uint8_t d4 = 10;
const uint8_t d5 = 11;
const uint8_t d6 = 12;
const uint8_t d7 = 13;

LiquidCrystal lcd (rs, en, d4, d5, d6, d7 );

void setup ()
{
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop ()
{
  lcd.setCursor(5,0);
  lcd.print("WORKING");
  lcd.setCursor(0,1);
  lcd.scrollDisplayLeft();
  lcd.print("0000 000000 0000 000000 000000 0000");
  delay(750); 
}
