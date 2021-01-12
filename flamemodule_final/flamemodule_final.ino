#include<SoftwareSerial.h>
int sensorpin=A1;
int sensorvalue=0;
int ledbuzz=12;
 int interval=1000;
int pm2=0;

void setup(){
  pinMode(ledbuzz,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  unsigned long currentmillis= millis();
  sensorvalue=analogRead(sensorpin);
  //Serial.println(sensorvalue);
  if(sensorvalue<100)
  {
    if(pm2-currentmillis>interval)
    {
      pm2=currentmillis;
      Serial.println("fire detected");
    digitalWrite(ledbuzz,HIGH);
    }
  
    //delay(500);
  }
  digitalWrite(ledbuzz,LOW);
  //delay(sensorvalue);
}

