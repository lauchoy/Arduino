#include <dht.h>

dht DHT;

#define DHT11_PIN 7
int led1 = 9;
int led2 = 10;
int led3 = 11;
int fetPin = 3;
const int pinUp = 255;
const int pinDown = 0;

void setup(){
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(fetPin, OUTPUT);  
}

void loop()
{
  //temp sensor reads every 2 seconds because its duty cycle is 1Hz
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature (Celsius): ");
  Serial.println(DHT.temperature);
  int temp = DHT.temperature;
  if(temp > 26.00){ //temperature is above 26C
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    analogWrite(fetPin, pinDown);
    delay(2000);
  }

  else if(temp < 20.00){ //what if the room is really cold?
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    analogWrite(fetPin, pinUp);
    delay(2000);
  } 
  else{ //stay on regardless
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    analogWrite(fetPin, pinUp);
    delay(2000);
  } 
  delay(2000);
}

