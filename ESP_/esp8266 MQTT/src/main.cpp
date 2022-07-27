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
  inti_WiFi("Segin","2003sejin");       //conectinng into network by using ssid,pasword
  inti_mqttBroker();
}

void loop()
{
  mqttClient.loop();
}
void inti_mqttBroker()       // to create a connection to a broker.
{

  mqttClient.setServer("5.196.95.208",1883);
  mqttClient.setCallback(mqttCallBack);
  Serial.print("Connecting...");
  while(mqttClient.connect("ESP.client",NULL,NULL) == false)
  {
    delay(100);
    Serial.print('.');

  }
  Serial.println();
  Serial.println("Connected to MQTT Broker");
  // Serial.println(mqttClient.state());

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