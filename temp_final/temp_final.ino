#include <math.h>

#define LATCH 6
#define CLK 5
#define DATA 3

byte digitTwo[10]={0b10000000, 0b11111001, 0b00100100, 0b00110000, 0b00011001, 0b00010010, 0b00000010, 0b11111000, 0b00000000, 0b00010000};
byte digitOne[10]={0b10111111, 0b00000110, 0b11011011, 0b11001111, 0b11100110, 0b11101101, 0b11111101, 0b00000111, 0b11111111, 0b11101111};

double Thermistor(int RawADC)
{ double temp;
temp=log(10000.0*((1024.0/RawADC-1)));
temp=1/(0.001129148+(0.000234125+(0.0000000876741*temp*temp))*temp);
temp=temp-273.15;
return temp;
}

void setup()
{
      pinMode(LATCH,OUTPUT);
      pinMode(CLK,OUTPUT);
      pinMode(DATA,OUTPUT);
      Serial.begin(9600);
}
void loop() {
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
      //delay(500);
      }


