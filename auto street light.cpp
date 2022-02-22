int ldrpin=A0;
int redled=2;
int greenled=3;
int ldrval;
int dt=100;
int relaypin=4;

void setup ()
{
  pinMode(ldrpin,INPUT);
  pinMode(redled,OUTPUT);
  pinMode(greenled,OUTPUT);
  pinMode(relaypin,OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  ldrval=analogRead(ldrpin);
  Serial.print("LDR val= ");
  Serial.println(ldrval);
  delay(dt);

 
    
  
  if(ldrval>250)
  {
    digitalWrite(greenled,HIGH);
    digitalWrite(redled,LOW);
    digitalWrite(relaypin,LOW);
  }
  if(ldrval>1000)
  {
    digitalWrite(greenled,LOW);
    digitalWrite(redled,HIGH);
    digitalWrite(relaypin,HIGH);
    Serial.println("              relay on           ");
  }
  
  
}
