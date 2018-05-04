/*Jimmy Lauchoy FInal Project */
/*Modified heat blanket source from Sparkfun*/

int btnPin = 2;
boolean btnPressed = false;
int fetPin = 3; //mosfet pin
int led1 = 9;
int led2 = 10;
int led3 = 11;
int tempPin = A2; //temperature sensor
int velReadLR;
int velReadTB;
int vel1 = A3; velostat left & right sides
int vel2 = A4; velostat top & bottom sides 
int mode;

void setup() {                
  // initialize the digital pin and 2 velostat pins as an output.
  pinMode(btnPin, INPUT);  
  pinMode(vel1, INPUT);
  pinMode(vel2, INPUT);
  pinMode(fetPin, OUTPUT);  
  pinMode(led1, OUTPUT);  
  pinMode(led2, OUTPUT);  
  pinMode(led3, OUTPUT);  
}

void loop() {
  //Increment mode on depress, unless mode = 3, then reset to 0
  if (btnPressed && digitalRead(btnPin) == LOW)
    if (mode = 3){
      mode - 0;
    }
    else{
      mode += 1;
    }
  //Assign button state
  btnPressed = digitalRead(btnPin);
  //Assign sensor reading
  velReadLR = analogRead(vel1);
  velReadTB = analogRead(vel2);
  switch (mode)
  {
    //vary heating degrees by each case
    case 0:
      analogWrite(fetPin, 0); //off
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      break;
    case 1:
      analogWrite(fetPin, 85); //33% duty cycle
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      break;
    case 2:
      analogWrite(fetPin, 170); //66% duty cycle
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      break;
    case 3:
      analogWrite(fetPin, 255); //100% duty cycle
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      break;
  }
}
