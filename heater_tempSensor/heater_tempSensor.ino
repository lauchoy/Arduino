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
  if(temp > 27.00){ //turn off if temperature is above 27C
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    //max for fetPin is 255, we want to lower the heat outputbut not turn it off
    analogWrite(fetPin, 70);
    delay(2000);
  }

  else if(temp < 20.00){ //room temperature is usually 21C to 23C, 
                         //anything lower than that, 
                         //the pillow heating should go on idle
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    analogWrite(fetPin, pinDown);
    delay(2000);
  } 
  else{ //turn on when the temperature reads anything higher than 20C
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    analogWrite(fetPin, pinUp);
    delay(2000);
  } 
  delay(2000);
}

