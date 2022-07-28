/*
2Q) Establish publish and subscribe system using any wireless communication protocols.

using mqtt protocol
with broker server test.mosquitto.org 
using esp 8266 nodeMcu
using mqtt lens for sub and pub
using platform.io
*/


# include <Arduino.h>
# include <ESP8266WiFi.h>
# include <PubSubClient.h>

WiFiClient espClient;
PubSubClient mqttClient(espClient);     //Now our client is called mqttClient


void inti_mqttBroker();
void inti_WiFi(String network_name, String network_password);
void mqttCallBack(char  *topic, byte *payload,  int length);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  inti_WiFi("Segin","2003sejin");       // conectinng into network by using ssid,pasword
  inti_mqttBroker();                    // connecting to the mqttBroker
}

void loop()
{
  mqttClient.loop();  
}


void inti_mqttBroker()       // to create a connection to a broker.
{

  mqttClient.setServer("5.196.95.208",1883); //using  test.mosquitto.org 
  mqttClient.setCallback(mqttCallBack); //function called when a message arrives 
  // for a subscription created by this client.
  Serial.print("Connecting...");
  while(mqttClient.connect("ESP.client",NULL,NULL) == false) //the client ID to use when connecting to the server
  {
    delay(100);
    Serial.print('.');

  }
  Serial.println();
  Serial.println("Connected to MQTT Broker");
/*

  just for debuging if req;

   Serial.println(mqttClient.state());

*/

  mqttClient.subscribe("/root/switch2");

}


void inti_WiFi(String network_name, String network_password)          // to intitalize esp8266 with wifi
{
  delay(100);
  Serial.println();
  WiFi.begin(network_name,network_password);    //wifi name, password
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED)            // if wifi not connected wait's untinl it gets conected
  {
    delay(500);
    Serial.print('.');
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());                       // just for printing out the ip add
  WiFi.printDiag(Serial);                               // data for diagnosing

}


void mqttCallBack(char  *topic, byte *payload,  int length)
{
  // just printing out the data in seril
  Serial.print("Message arrived on Topic: ");
  Serial.println(topic);
  

  char msg [5] = {0x00};
  for (int i = 0; i < length; i++)
  {
    msg[i] = (char)payload[i];
  }
  msg[length] = 0x00;
  Serial.println(msg);

}