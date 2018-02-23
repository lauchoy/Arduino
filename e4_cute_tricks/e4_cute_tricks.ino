int light = 0; // store the current light value

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600); //configure serial to talk to computer
    pinMode(13, OUTPUT); // configure digital pin 13 as an output
    pinMode(12, OUTPUT); // configure digital pin 12 as an output
    pinMode(9, OUTPUT); //configure digital pin 9 as an output
}


void loop() {
    // put your main code here, to run repeatedly:
    light = analogRead(A0); // read and save value from photo resistor
    
    Serial.println(light); // print current light value
 
    if(light > 420) { // If it is bright...
        Serial.println("It is VERY bright!");
        digitalWrite(13,LOW); //turn left LED off
        digitalWrite(12,LOW); // turn right LED off
    }
    else if(light > 140 && light < 419) { // If it is average light...
        Serial.println("It is NORMAL bright!");
       digitalWrite(13, HIGH); // turn left LED on
       digitalWrite(12,LOW);  // turn right LED off
    }
    else { // If there's little light...
        Serial.println("It is NOT bright!");
      
        digitalWrite(13,HIGH); // Turn left LED on
        digitalWrite(12,HIGH); // Turn right LED on
    }
    delay(1000); // 1 second updates

      // fade in from min to max in increments of 5 points: //from Fade example
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(9, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(9, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}
