# include <Arduino.h>
# include <ESP8266WiFi.h>

void init_wifi(String network_name, String network_password );


void setup()
{
  Serial.begin(115200);
  Serial.println();

  init_wifi("Segin","2003sejin");
}

void loop()
{
  
}

void init_wifi(String network_name, String network_password )
{
  delay(50);
  WiFi.begin(network_name,network_password);
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print('.');
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  WiFi.printDiag(Serial);

}