// include the library code:
#include <ShiftedLCD.h>
#include <SPI.h>
//#include <LiquidCrystal.h>

// initialize the library with the number of the sspin
// (or the latch pin of the 74HC595)
LiquidCrystal lcd(10);

int trigPin = 4; //trig pin 4
int echoPin = 6; //echo pin 6
int lightPin = A0; //light sensor pin A0;
float pingTime; //amount of time it takes for the sensor to hit the target
float targetDistance; //distance from target
float speedOfSound = 776.5; //speed of sound in mph

void reset() {
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}
void darkFar() {
  // set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  lcd.print("you will be");
  // set cursor to column 0, line 1
  lcd.setCursor(0, 1);
  lcd.print("hungry soon.");
  delay(2000);
};

void darkClose() {
  // set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  lcd.print("whatever happens,");
  // set cursor to column 0, line 1
  lcd.setCursor(0, 1);
  lcd.print("happens.");
  delay(2000);
  reset();
};

void darkVClose() {
  // set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  lcd.print("be a warrior");
  // set cursor to column 0, line 1
  lcd.setCursor(0, 1);
  lcd.print("not a worrier");
  delay(2000);
  reset();
}

void brightFar() {
  // set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  lcd.print("life's your cup");
  // set cursor to column 0, line 1
  lcd.setCursor(0, 1);
  lcd.print("drink it up");
  delay(2000);
  reset();
}

void brightClose() {
  // set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  lcd.print("you become");
  // set cursor to column 0, line 1
  lcd.setCursor(0, 1);
  lcd.print("what you believe");
  delay(2000);
  reset();
}

void brightVClose() {
  // set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  lcd.print("go ahead,");
  // set cursor to column 0, line 1
  lcd.setCursor(0, 1);
  lcd.print("make my day");
  delay(2000);
  reset();
}

void vBrightFar() {
  // set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  lcd.print("promise yourself");
  // set cursor to column 0, line 1
  lcd.setCursor(0, 1);
  lcd.print("happiness");
  delay(2000);
  reset();
}

void vBrightClose() {
  // set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  lcd.print("go back a lil");
  // set cursor to column 0, line 1
  lcd.setCursor(0, 1);
  lcd.print("to leap further");
  delay(2000);
  reset();
}

void vBrightVClose() {
  // set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  lcd.print("live like no");
  // set cursor to column 0, line 1
  lcd.setCursor(0, 1);
  lcd.print("one before");
  delay(2000);
  reset();
}


void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
}

void loop() {
  int lightVal = analogRead(lightPin); //read light value from sensor

  digitalWrite(trigPin, LOW); //set trigger pin low
  delayMicroseconds(2000); //delay in low state
  digitalWrite(trigPin, HIGH); //set trigger pin high
  delayMicroseconds(25); //delay in high state
  digitalWrite(trigPin, LOW); //ping is sent
  delayMicroseconds(10);

  pingTime = pulseIn(echoPin, HIGH); //pingTime is received in microseconds
  pingTime = pingTime / 1000000; //convert to seconds
  targetDistance = (speedOfSound * pingTime); //get foot measurement
//  lcd.setCursor(0, 0);
//  lcd.print(lightVal);
//  lcd.setCursor(0, 1);
//  lcd.print(targetDistance);

  if (lightVal >= 700) {
    if (targetDistance >= 2.50) {
      darkFar();
    }
    else if (targetDistance <= 1.00) {
      darkVClose();
    }
    else if (targetDistance < 3.50 || targetDistance > 1.00) {
      darkClose();
    }
  }
  else if (lightVal < 700 && lightVal > 150) {
    if (targetDistance >= 3.50) {
    brightFar();
    }
    else if (targetDistance < 1.00) {
    brightVClose();
    }
    else if (targetDistance < 3.50 || targetDistance > 1.00) {
    brightClose();
    }
  }

  else if (lightVal <= 150) {
    if (targetDistance >= 3.50) {
      vBrightFar();
    }
    else if (targetDistance < 1.00) {
      vBrightVClose();
    }
    else if (targetDistance < 3.50 || targetDistance > 1.00) {
      vBrightClose();
    }
  }

  delay(250);
}
