#include<SoftwareSerial.h>
#include <math.h>

//gas
int fan=7;
int greenled=11;
int buzz=13;
int gas_value;
int gas_avalue;
int sensorThres=100;

//temperture
#define LATCH 6
#define CLK 5
#define DATA 2
byte digitTwo[10]={0b10000000, 0b11111001, 0b00100100, 0b00110000, 0b00011001, 0b00010010, 0b00000010, 0b11111000, 0b00000000, 0b00010000};
byte digitOne[10]={0b10111111, 0b00000110, 0b11011011, 0b11001111, 0b11100110, 0b11101101, 0b11111101, 0b00000111, 0b11111111, 0b11101111};
double Thermistor(int RawADC)
{ double temp;
temp=log(10000.0*((1024.0/RawADC-1)));
temp=1/(0.001129148+(0.000234125+(0.0000000876741*temp*temp))*temp);
temp=temp-273.15;
return temp;
}


//PIR
int calibrationTime = 30;
long unsigned int lowIn;
long unsigned int pause = 5000;  
boolean lockLow = true;
boolean takeLowTime;
int pirPin = 4;
int ledPinP = 10;
int counter=0;
long previousmills=0;
long previousmillis1=0;
int interval=1000;
  

//flame
int sensorpin=A1;
int sensorvalue=0;
int ledbuzz=12;

//LDR
const int lightPin = A0;
const int ledPinLDR = 9;
int lightLevel; 
 
void setup ( ) { 
  pinMode(ledPinLDR, OUTPUT);
 pinMode(ledbuzz,OUTPUT);
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPinP, OUTPUT);
  digitalWrite(pirPin, LOW);
  pinMode(fan,OUTPUT);
  pinMode(buzz,OUTPUT);
  pinMode(greenled,OUTPUT);
  pinMode(3,INPUT);
digitalWrite(fan, LOW);
  
 
  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);

 pinMode(LATCH,OUTPUT);
      pinMode(CLK,OUTPUT);
      pinMode(DATA,OUTPUT);
      Serial.begin(9600);
  
 } 
 
void loop ( ) { 
  unsigned long currentmillis= millis();
      //PIR
     if(digitalRead(pirPin) == HIGH){
         //the led visualizes the sensors output pin state
         //delay(3000);
         if (currentmillis-previousmills>4*interval)
         {
          previousmills=currentmillis;
          counter++;
       //delay(2000);
       Serial.println("no.of preople : ");
       Serial.println(counter);
         }
       
       if(counter%4==0)
       {
        digitalWrite(ledPinP, HIGH);
        //delay(1000);
        if (currentmillis-previousmillis1>interval)
        {
          previousmillis1=currentmillis;
          digitalWrite(ledPinP,LOW );
        }
        
        }
       if(lockLow){ 
         //makes sure we wait for a transition to LOW before any further output is made:
         lockLow = false;           
         
         delay(50);
         }        
         takeLowTime = true;
       }
 
     if(digitalRead(pirPin) == LOW){      
       digitalWrite(ledPinP, LOW);  //the led visualizes the sensors output pin state
 
       if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
       //if the sensor is low for more than the given pause,
       //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause){ 
           //makes sure this block of code is only executed again after
           //a new motion sequence has been detected
           lockLow = true;                       
           
           delay(50);
           }
       }

//flame
 sensorvalue=analogRead(sensorpin);
 
  if(sensorvalue<100)
  {
    Serial.println("fire detected");
    digitalWrite(ledbuzz,HIGH);
    delay(500);
  }
  digitalWrite(ledbuzz,LOW);
  //delay(sensorvalue);


//LDR
 lightLevel = analogRead(lightPin);
lightLevel = map(lightLevel, 100, 500, 0, 255);
lightLevel = constrain(lightLevel, 0, 255);
analogWrite(ledPinLDR,255-lightLevel);




//temperture
int val;
      double temp;
      int tempD;
      val= analogRead(A2);
      temp=Thermistor(val);
      tempD = round(temp);
      Serial.println(tempD);
      
      int tens = (tempD - (tempD%10))/10;
      int ones = tempD%10;

      digitalWrite(LATCH,LOW);
      shiftOut(DATA, CLK, MSBFIRST, ~digitTwo[tens]);
      shiftOut(DATA, CLK, MSBFIRST, ~digitOne[ones]);
      digitalWrite(LATCH,HIGH);
      //delay(1000);

      //gas
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
