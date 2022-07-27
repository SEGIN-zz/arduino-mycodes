/*
* pin connections
 
driver ============= Arduino uno
    IN 1 ========>>  pin 8
    IN 2 ========>>  pin 9
    IN 3 ========>>  pin 10
    IN 4 ========>>  pin 11
  
  plz use this config if using this code
  
*/


# include <Arduino.h>
# include <Stepper.h>

int spr = 2048;
int mot_speed = 10;
int dt = 500;
Stepper Stepper_zero (spr,8,10,9,11);

void setup()
{
  Serial.begin(9600);
  Stepper_zero.setSpeed(mot_speed);
}

void loop ()
{
  Stepper_zero.step(spr);
  delay(dt);
  Stepper_zero.step(-spr);
  delay(dt);
}
