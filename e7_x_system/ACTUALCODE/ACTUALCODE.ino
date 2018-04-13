#include <SPI.h>
#include <WiFi101.h>
#include <WiFiSSLClient.h>
#include <TembooSSL.h>
#include "utility/TembooGPIO.h"
#include "TembooAccount.h" // Contains Temboo account information

WiFiSSLClient client;

//zipcodes are preset to New York, Wyoming, Florida, Arizona
String zips[]={"10012", "82941", "33124", "85001"};
String rain[]={"5","6","7","8","9","10","11","12","40","41","42","43"};
String thunderstorm[]={"37","38","39","45","47"}
String cloudy[]={"20","21","22","23","26","27","28","29","30"};
// These are the Arduino pins connected to your shift register string
const int ShiftPWM_latchPin=8;
const int ShiftPWM_dataPin = 6; //changed pin from 11 to 6 for wifi shield
const int ShiftPWM_clockPin = 12;

// The number of 8-bit shift registers connected 
const unsigned int ShiftPWM_numRegisters=2;       // The number of 8-bit shift registers connected

// If your LED's turn on if the pin is low, set this to true, otherwise set it to fals
const bool ShiftPWM_invertOutputs = false; 

// You can enable the option below to shift the PWM phase of each shift register by 8 compared to the previous.
// This will slightly increase the interrupt load, but will prevent all PWM signals from becoming high at the same time.
// This will be a bit easier on your power supply, because the current peaks are distributed.
const bool ShiftPWM_balanceLoad = false;

#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!


unsigned char maxBrightness = 255;
int pwmFrequency=100;

int numRGBleds = ShiftPWM_numRegisters*8/3;
int buttonState = 0; 
int button = 10; 
int prevState = 0; 
String zipCondition;

int counter; 
// We limit this so you won't use all of your Temboo calls while testing
int maxCalls = 10;

// The number of times this Choreo has been run so far in this sketch
int calls = 0;

// Declaring sensor configs
TembooGPIOConfig tmb_rgb1Config;

// Declaring TembooSensors
TembooActuator tmb_rgb1;

void setup() {
  Serial.begin(9600);
  
  // For debugging, wait until the serial console is connected
  delay(4000);
  while(!Serial);

  int wifiStatus = WL_IDLE_STATUS;

  // Determine if the WiFi Shield is present
  Serial.print("\n\nShield:");
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("FAIL");

    // If there's no WiFi shield, stop here
    while(true);
  }

  Serial.println("OK");

  // Try to connect to the local WiFi network
  while(wifiStatus != WL_CONNECTED) {
    Serial.print("WiFi:");
    wifiStatus = WiFi.begin(WIFI_SSID, WPA_PASSWORD);

    if (wifiStatus == WL_CONNECTED) {
      Serial.println("OK");
    } else {
      Serial.println("FAIL");
    }
    delay(5000);
  }

  // Initialize sensors and configs
  tembooDigitalGPIOInit(&tmb_rgb1Config, &tmb_rgb1, 6, LOW, OUTPUT);
  Serial.println("Setup complete.\n");
  pinMode(button, OUTPUT); 
  // SetPinGrouping allows flexibility in LED setup. 
  ShiftPWM.SetPinGrouping(1); //This is the default, but I added here to demonstrate how to use the funtion
  
  ShiftPWM.Start(pwmFrequency,maxBrightness); //start the rgb LEDs
}

void loop() {
  if (calls < maxCalls) {
    Serial.println("Calling GetWeatherByAddress Choreo...");
    runGetWeatherByAddress(zips[0]);
    calls++;
  } else {
    Serial.println("Skipping to save Temboo calls. Adjust maxCalls as required.");
  }
  delay(30000);

//cycle through weather regions with preset zipcodes
//0 to northeast, 1 to southeast, 2 to midwest, 3 to southwest
  buttonState = digitalRead(button); 
  if (buttonState != prevState){
    if (buttonState == HIGH){
      counter++; 
      Serial.println(counter); 
      runGetWeatherByAddress(zips[counter]); //changes to next zip code
      changeLED(counter);
      zipCondition = Serial.read();
      if (isRaining(zipCondition) == true){
        rain();
      }
      else if(isThunder(zipCondition) == true){
        thunderstorm();
      }
      else if(isCloudy(zipCondition) == true){
        cloudy();
      }
    }else{
      Serial.println("not being pushed"); 
    }
    delay(50); 
  }
  prevState = buttonState; 

  if (counter > 4){ //resets counter and resets position in zipcode array
    counter = 0;
  }
}
void runGetWeatherByAddress(String zipcode) {
  TembooChoreoSSL GetWeatherByAddressChoreo(client);

  // Set Temboo account credentials
  GetWeatherByAddressChoreo.setAccountName(TEMBOO_ACCOUNT);
  GetWeatherByAddressChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
  GetWeatherByAddressChoreo.setAppKey(TEMBOO_APP_KEY);
  GetWeatherByAddressChoreo.setDeviceType(TEMBOO_DEVICE_TYPE);
  // Set Choreo inputs
  String AddressValue = zipcode;
  GetWeatherByAddressChoreo.addInput("Address", AddressValue);
  // Identify the Choreo to run
  GetWeatherByAddressChoreo.setChoreo("/Library/Yahoo/Weather/GetWeatherByAddress");

  // Run the Choreo
  unsigned int returnCode = GetWeatherByAddressChoreo.run();

  // A return code of zero means everything worked
  if (returnCode == 0) {
    tmb_rgb1.write(&tmb_rgb1Config, HIGH);
  }

  GetWeatherByAddressChoreo.close();
}

void changeLED(int number){
  if (number == 0){
    northeast();
  }
  else if (number == 1){
    southeast();
  }
  else if (number == 2){
    midwest();
  }
  else if (number == 3){
    southwest();
  }
}
void northeast(){ //cool, blue, teal colors
  ShiftPWM.SetRGB(0,0,255,0);    //(BLUE, RED, GREEN) 
  ShiftPWM.SetRGB(1,0,255,0);
  ShiftPWM.SetRGB(2,128,0,255);
  ShiftPWM.SetRGB(3,255,128,0);
  ShiftPWM.SetRGB(4,255,0,0);
}

void southeast(){ //tropical colors, pink, orange, skyblue, cyan
  ShiftPWM.SetRGB(0,255,255,0);    //(BLUE, RED, GREEN) 
  ShiftPWM.SetRGB(1,0,255,128);
  ShiftPWM.SetRGB(2,0,0,255);
  ShiftPWM.SetRGB(3,0,128,0);
  ShiftPWM.SetRGB(4,255,0,128);  
}

void midwest(){ //cold forestry, green and gray
  ShiftPWM.SetRGB(255,0,255,0);    //(BLUE, RED, GREEN) 
  ShiftPWM.SetRGB(1,0,255,0);
  ShiftPWM.SetRGB(2,255,0,255);
  ShiftPWM.SetRGB(3,255,128,0);
  ShiftPWM.SetRGB(4,255,0,255);
}

void southwest(){ //hot and dry, deep orange, pink, and sand 
  ShiftPWM.SetRGB(0,0,255,0);    //(BLUE, RED, GREEN) 
  ShiftPWM.SetRGB(1,0,255,255);
  ShiftPWM.SetRGB(2,255,0,128);
  ShiftPWM.SetRGB(3,255,128,0);
  ShiftPWM.SetRGB(4,128,0,255);
}

void rain(){ ///randomly flash a LED, blinking pattern
  ShiftPWM.SetRGB(random(numRGBleds),0,0,0);
  delay(random(10,200));
}

bool isRainy(String condVal){
  for(i = 0; i < sizeof(rain); i++){
    if (rain[i] == condVal){
      return true;
    }
  }
  return false;
}

bool isThunder(String condVal){
  for(i = 0; i < sizeof(thunderstorm); i++){
    if (thunderstorm[i] == condVal){
      return true;
    }
  }
  return false;
}

bool isCloudy(String condVal){
  for(i = 0; i < sizeof(cloudy); i++){
    if (cloudy[i] == condVal){
      return true;
    }
  }
  return false;
}
void thunderstorm(){ //randomly flash all LEDs at a random time
  ShiftPWM.SetAll(0);
  delay(random(10,5000));
}

void cloudy(){ //hazy, low visibility
  // Fade in all outputs
  for(int j=80;j<170;j++){
    ShiftPWM.SetAll(j);  
    delay(20);
  }
  // Fade out all outputs
  for(int j=80;j>=0;j--){
    ShiftPWM.SetAll(j);  
    delay(20);
  }
}



