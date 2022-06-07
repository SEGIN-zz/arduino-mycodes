# include<Arduino.h>
# include<PID_v1.h>

double PidSetPoint,PidInput,PidOutput;
double kp = 1;
double ki = 0;
double kd = .035;

PID motorPID( &PidInput,&PidOutput,&PidSetPoint,kp,ki,kd,DIRECT);

const uint8_t feedbackPot = A0;
const uint8_t motorEnablePin = 6;
const uint8_t motorDirection1 = 5;
const uint8_t motorDirection2 = 4;

int myPos = 90;

int inputVal ;
int pwmVal = 150;
int potMax = 958;
int potMin = 342; 

void setup()
{
  pinMode(feedbackPot,INPUT);
  pinMode(motorEnablePin,OUTPUT);
  pinMode(motorDirection1,OUTPUT);
  pinMode(motorDirection2,OUTPUT);
  Serial.begin(9600);

  motorPID.SetMode(AUTOMATIC);
  motorPID.SetOutputLimits(-225,225);
  motorPID.SetSampleTime(20);
  
}


void loop()
{
  
  inputVal = analogRead(feedbackPot);
  Serial.print("feedback pot : ");
  Serial.print(inputVal);
  PidSetPoint = map(myPos,0,180,0,180);
  Serial.print(" pid Set point : ");
  Serial.print(PidSetPoint);
  PidInput = map(inputVal,potMin,potMax,0,180);
  Serial.print(" pid input : ");
  Serial.print(PidInput);
  motorPID.Compute();
  Serial.print(" pidoutput : ");
  Serial.println(PidOutput);
  

  if (PidOutput < 0 )
  {
    //pwmVal = PidOutput;
    analogWrite(motorEnablePin,pwmVal);
    digitalWrite(motorDirection1,HIGH);

  }
  if(PidOutput > 0)
  {
    //pwmVal = abs(PidOutput);
    analogWrite(motorEnablePin,pwmVal);
    digitalWrite(motorDirection2,HIGH);
  }







}
