# include <Arduino.h>
# include <Servo.h>

Servo myServo; 
int servoPin = 2;

void setup()
{
  Serial.begin(9600);
  myServo.attach(servoPin);
}

void loop()
{
  for(int i = 0; i < 180; i++)
  {
    myServo.write(i);
    delay(100);
  }
  for (int j = 180; j > 0; j--)
  {
    myServo.write(j);
    delay(100);
  }
}