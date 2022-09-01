#include <Arduino.h>
#include <HardwareSerial.h>

HardwareSerial SerialPort(2); // use UART2


void setup()  
{
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);
  pinMode(2,OUTPUT); 
} 
void loop()  
{ 
  
  SerialPort.print(1);
  delay(100);
  SerialPort.print(0);
  delay(100);
}