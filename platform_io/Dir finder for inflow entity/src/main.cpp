/*

1Q) What sensor can you use to find the direction of any inflow entity?
Write the code for the selected sensor to print the direction detected.
(Use any MC: NodeMCU, RPi, UNO, Nano, Mega, ESP, MSP)(Entity - consider a bowling system where the ball is your entity)

Ans : considering a bowling system  a ball that goes through a channel therefore, 
i will be using object detection ,using ldr and led for object detection 
there will be a array of led and ldr equaly spaced this spaing should be 
propotional to the size & speed of the entitiy also its logic is similar to 
a rotary encoder this way it is cheap, and effective;

using arduino uno;
using platform.io 

*/

 # include <Arduino.h>        
// this  is for including arduino frameWork in platform.io

class Detector                 
{
// pair of a led and  ldr together form this object called Detector
// this object stores & gets data
 
  private: 
// init pins for led & ldr
    int _ledPin;                
    int _ldrPin;
    int _ldrVal;
// used to store ldr val
    int _detectioin_status;    
// used to store detecion status
  
  public:
/*
 init_detector is used  intizing  the detector,  
 this function takes two arg, pinNumber of led and ldr
 by this we can init how many detectors that we want;
*/
    void init_detector(int ledPin, int ldrPin)          
    {
      _ledPin = ledPin;
      _ldrPin = ldrPin;
      pinMode(_ledPin,OUTPUT);                          
      pinMode(_ldrPin,INPUT);
      // Serial.println("setupComplete ...");               // just  4 debuging
    }
/*
stat_detecion is used to stat the detector it turns on the
led and reads the ldr pin and prints the ldr val 
led turns on and the ldr recives the light 
*/
    void start_detection()                            
    {
      digitalWrite(_ledPin,HIGH);
      _ldrVal = analogRead(_ldrPin);
      Serial.println(_ldrVal);
      Serial.println("detection started");
    }
/* 
get_detectionStatus is used for getting status of the current condition
LDR is a component that has aresistance that changes with the light intensity that falls upon it. 
thus when the led light falls upon it we can assume that there is no objet there
when the light of led doesnot fall upon ldr we can asume that the object is detected
in this case a bowling ball
*/

    int get_detectionStatus()                         
    {
      _ldrVal = analogRead(_ldrPin);
// reading the val of ldr
/* 
logic for the ball detection if the ball is detected
it returns a 1, if not detected return 0;
*/
      if (_ldrVal >= 1000) // 1000 is a asumed val
      {
         _detectioin_status = 1;          
      }
      else 
      {
         _detectioin_status = 0;
      }
      return _detectioin_status;
    }

};
/*
constructing 3 objects as detectors 
*/
Detector detectorOne, detectroTwo, detectorThree;

void setup()
{
  Serial.begin(11500);  // used to begin and set baudrate of a serial monitor;
/*
now we need to inti the detector, i will be using 3 detector combo 
intitzing the objects it takes two input first led pin & second ldrPin
*/
  detectorOne.init_detector(2,A0);
  detectroTwo.init_detector(3,A1);
  detectorThree.init_detector(5,A2);

// now we need to start the detetion 
  detectorOne.start_detection();
  detectroTwo.start_detection();
  detectorThree.start_detection();      
}

void loop()
{

/* 
logic for ball detection
if the first detector satate is 1 and the rest of the detector state is low
we can asume that the ball is mooving forward;

**note
detectors are kept in a order left to right 
1 detector at the left side , 2 in middle and third at last
if this orentaion is chagned you will need to change the direction ;
*/

  if(detectorOne.get_detectionStatus() == 1 && detectroTwo.get_detectionStatus() == 0 
  && detectorThree.get_detectionStatus() == 0)
  {

    Serial.println("Forward");
    // printing the direction

  }
/* 
if the third detector satate is 1 and the rest of the detector state is  0
we can asume that the ball is mooving backwards;

**note
detectors are kept in a order left to right 
1 detector at the left side to 2 in middle and third at last
if this orentaion is chagned you will need to change the direction in this also;
*/

  if (detectorThree.get_detectionStatus() == 1 && detectroTwo.get_detectionStatus() == 0 
  && detectorOne.get_detectionStatus() == 0)
  {

    Serial.println("Backward");
    // printing the direction

  }
/*
this will be working in a infinit loop for the ball detecion
*/


}