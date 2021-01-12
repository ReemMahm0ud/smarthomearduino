//Example_5_Light_Sensor_led
const int lightPin = A0;
const int ledPin = 9;

int lightLevel; 
 
void setup ( ) {   pinMode(ledPin, OUTPUT);  } 
 
void loop ( ) {  lightLevel = analogRead(lightPin);
lightLevel = map(lightLevel, 100, 500, 0, 255);
lightLevel = constrain(lightLevel, 0, 255);
analogWrite(ledPin,255-lightLevel);
}
