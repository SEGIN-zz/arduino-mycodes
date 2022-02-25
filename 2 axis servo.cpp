#include<Arduino.h>
#include<Servo.h>

int potOnepin = A0;
int potOneval;
int potTwopin = A1;
int potTwoval;

Servo servoZero;
const byte servoZeropin = 2;
byte servoZeropos;
Servo servoOne;
const byte servoOnepin = 3;
byte servoOnepos;

const byte ledone = 13;
int ledstate1 = LOW;
const byte ledtwo = 12;
int ledstate2 = HIGH;
const byte ledthree = 11;
const long interval = 100;
unsigned long prevtime = 0;


void setup()
{
    Serial.begin(9600);

    pinMode(potOnepin,INPUT);
    pinMode(potTwopin,INPUT);

    servoZero.attach(servoZeropin);
    servoOne.attach(servoOnepin);
    
    pinMode(ledone,OUTPUT);
    pinMode(ledtwo,OUTPUT);
    pinMode(ledthree,OUTPUT);
    digitalWrite(ledthree,HIGH);

}


void loop()
{ 
    unsigned long currtime = millis();

    if (currtime - prevtime >= interval)
    {
         prevtime = currtime;

         if (ledstate1 == LOW || ledstate2 == HIGH)
         {
             ledstate1 = HIGH;
             ledstate2 = LOW;
         }
         else
         {
             ledstate1 = LOW;
             ledstate2 = HIGH;
         }
         digitalWrite(ledone,ledstate1);
         digitalWrite(ledtwo,ledstate2);
    }

    potOneval = analogRead(potOnepin);
    Serial.print(potOneval);
    potTwoval = analogRead(potTwopin);
    Serial.println(potTwoval);

    servoZeropos = (180./1023.)*potOneval;
    servoZero.write(servoZeropos);
    Serial.print(servoZeropos);
    servoOnepos = (180./1023.)*potTwoval;
    servoOne.write(servoOnepos);
    Serial.print("    ");
    Serial.println(servoOnepos);
}
