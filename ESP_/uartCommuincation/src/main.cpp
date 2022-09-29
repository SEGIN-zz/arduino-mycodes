#include <Arduino.h>
#include <HardwareSerial.h>

HardwareSerial cerial(2);

void setup()
{
  Serial.begin(115200);
  cerial.begin(115200,SERIAL_8N1,17,16);
  delay(1000);
}

void loop()
{

  while(cerial.available() == 0)
  {
    // Serial.print("No cerial");
    delay(100);
    Serial.print(".");
  }
  Serial.println(cerial.readStringUntil('\n'));
}