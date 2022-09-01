# include <Arduino.h>
# include <RTClib.h>
# include <SPI.h>

RTC_DS1307 rtc;

void setup()
{
  Serial.begin(115200);

  if (!rtc.begin())
  {
    Serial.println("RTC missing! ");
    Serial.flush();
    while(true) delay(10);
  }

  if(!rtc.isrunning())
  {
    Serial.println("RTC not running set date and time.");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    rtc.adjust(DateTime(2022, 9, 1, 9, 21, 1));

  }


}

void loop()
{
  DateTime time = rtc.now();

 //Full Timestamp
 Serial.println(time.timestamp(DateTime::TIMESTAMP_DATE)+("::data0x00"));

//  //Date Only
//  Serial.println(String("DateTime::TIMESTAMP_DATE:")+time.timestamp(DateTime::TIMESTAMP_DATE));

//  //Full Timestamp
//  Serial.println(String("DateTime::TIMESTAMP_TIME:")+time.timestamp(DateTime::TIMESTAMP_TIME));
delay(100); 

}