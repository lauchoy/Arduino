#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h" // contains Temboo account information, as described below

int calls = 1;   // Execution count, so this doesn't run forever
int maxCalls = 10;   // Maximum number of times the Choreo should be executed
char character; //makes space for the xml spreadsheet
String content = ""; //adds a part to the string. it ads the qote to the string.

int redLED = 6; 
int bluLED = 9; 
int yellowLED = 10; 
int ledBRITE = 255;
int ledWAVE; 
void setup() {
  Serial.begin(9600);
  
  // For debugging, wait until the serial console is connected
  delay(4000);
  while(!Serial);
  Bridge.begin();
}

void loop() {
  if (calls <= maxCalls) {
    Serial.println("Running WeatherByZipcode - Run #" + String(calls++));
    
    TembooChoreo WeatherByZipcodeChoreo;

    // Invoke the Temboo client
    WeatherByZipcodeChoreo.begin();

    // Set Temboo account credentials
    WeatherByZipcodeChoreo.setAccountName(TEMBOO_ACCOUNT);
    WeatherByZipcodeChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    WeatherByZipcodeChoreo.setAppKey(TEMBOO_APP_KEY);
    
    // Set profile to use for execution
    WeatherByZipcodeChoreo.setProfile("MyCurrentWeather");
    
    // Identify the Choreo to run
    WeatherByZipcodeChoreo.setChoreo("/Library/NOAA/WeatherByZipcode");
    
    // Run the Choreo; when results are available, print them to serial
    WeatherByZipcodeChoreo.run();
    
    while(WeatherByZipcodeChoreo.available()) {
      char c = WeatherByZipcodeChoreo.read();
      Serial.print(c);
      
    }
    
    if( temp > 100){
        if(API TEMP INFO NORMAL){
    analogWrite(redLED, ledBRITE); 
    analogWrite(bluLED, (ledBRITE/2));
    analogWrite(yellowLED, ledBRITE); 
  }
  else if (API TEMP INFO HEATWAVE){
    analogWrite(bluLED, 0);
    for(int j = 100; i < 255; i+=5){
      analogWrite(yellowLED, j)
    }
    for(int i = 0; i < 255; i+=5){
      analogWrite(redLED, i); 
    }
    delay(30);
    if (i == 0 && j == 0){
      for (i = 255; i > 0; i-=5){
        analogWrite(redLED, i);
      }
      for(j = 255; j > 100; j-=5){
        analogWrite(yellowLED,j); 
      }
      delay(30); 
    }
  }
    }
    WeatherByZipcodeChoreo.close();
  }

  Serial.println("Waiting...");
  delay(30000); // wait 30 seconds between WeatherByZipcode calls
}

