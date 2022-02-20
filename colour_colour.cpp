int redpin=12;
int greenpin=11;
int bluepin=10;
String msg="color color which color do you want?";
String mycolor;

void setup()
{
  pinMode(redpin,OUTPUT);
  pinMode(greenpin,OUTPUT);
  pinMode(bluepin,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  Serial.println(msg);
while (Serial.available()==0)
     {
       //do nothing;
     }
  mycolor=Serial.readString();
if (mycolor=="red")
    {
      digitalWrite(redpin,HIGH);
      digitalWrite(greenpin,LOW);
      digitalWrite(bluepin,LOW);
    }
if (mycolor=="green")
    {
      digitalWrite(redpin,LOW);
      digitalWrite(greenpin,HIGH);
      digitalWrite(bluepin,LOW);
    }
if (mycolor=="blue")
    {
      digitalWrite(redpin,LOW);
      digitalWrite(greenpin,LOW);
      digitalWrite(bluepin,HIGH);
    }
}
