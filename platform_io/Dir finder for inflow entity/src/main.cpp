/*

1Q) What sensor can you use to find the direction of any inflow entity?
Write the code for the selected sensor to print the direction detected.
(Use any MC: NodeMCU, RPi, UNO, Nano, Mega, ESP, MSP)(Entity - consider a bowling system where the ball is your entity)

Ans) 

considering a bowling system  a ball that goes through a channel 

therefore, i will be using object detection ,using ldr and led for object detection

*/



 # include <Arduino.h>



class Detector
{
  
  private:

    int _ledPin;
    int _ldrPin;
    int _ldrVal;
    int _detectioin_status;

  public:


    void init_detector(int ledPin, int ldrPin)          // inti the detector
    {
      _ledPin = ledPin;
      _ldrPin = ldrPin;
      pinMode(_ledPin,OUTPUT);
      pinMode(_ldrPin,INPUT);
      Serial.println("setupComplete ...");
    }

    void start_detection()
    {
      digitalWrite(_ledPin,HIGH);
      _ldrVal = analogRead(_ldrPin);
      Serial.println(_ldrVal);
      Serial.println("detection started");
    }

    int get_detectionStatus()                         // to get status
    {
      _ldrVal = analogRead(_ldrPin);
      if (_ldrVal >= 1000)
      {
         _detectioin_status = 1;          
      }
      else 
      {
         _detectioin_status = 0;
      }
      return _detectioin_status;
      
      Serial.println("detection approved");
    }

};

Detector detectorOne, detectroTwo, detectorThree;

void setup()
{
  Serial.begin(11500);

  detectorOne.init_detector(2,A0);
  detectroTwo.init_detector(3,A1);
  detectorThree.init_detector(5,A2);

  detectorOne.start_detection();
  detectroTwo.start_detection();
  detectorThree.start_detection();      // statring detection;

}

void loop()
{

  // logic for ball detection 

  if(detectorOne.get_detectionStatus() == 1 && detectroTwo.get_detectionStatus() == 0 
  && detectorThree.get_detectionStatus() == 0)
  {

    Serial.println("Forward");

  }

  if (detectorThree.get_detectionStatus() == 1 && detectroTwo.get_detectionStatus() == 0 
  && detectorOne.get_detectionStatus() == 0)
  {


    Serial.println("Backward");

  }


}