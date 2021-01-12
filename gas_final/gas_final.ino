int fan=6;
int greenled=11;
int buzz=13;
int gas_value;
int gas_avalue;
int sensorThres=100;

void setup()
{
  pinMode(fan,OUTPUT);
  pinMode(buzz,OUTPUT);
  pinMode(greenled,OUTPUT);
  pinMode(3,INPUT);
digitalWrite(fan, LOW);
  Serial.begin(9600);
}
void loop()
{
  gas_avalue=digitalRead(3);
  if(gas_avalue==LOW)
  {
    digitalWrite(fan,HIGH);
    digitalWrite(greenled,LOW);
    digitalWrite(buzz,HIGH);
    Serial.println("DANGER");
    Serial.println(gas_avalue);
  }
  else
  {
    
    digitalWrite(greenled,HIGH);
    digitalWrite(buzz,LOW);
    Serial.println("NO DANGER");
  }
  delay(100);
}

