const int motor1Pin = 2;    // H-bridge leg 1 (pin 2)
const int switchPin = 3;    // switch input
const int motor2Pin = 4;    // H-bridge leg 2 (pin 7)
const int enablePin = 9;    // H-bridge enable pin
int pinValue;
bool currSwitchState = LOW;
bool prevSwitchState = LOW;
//In the setup(), set all the pins for the H-bridge as outputs, and the pin for the switch as an input. The set the enable pin high so the H-bridge can turn the motor on.

void setup() {
  Serial.begin(9600);
  // set the switch as an input:
  pinMode(switchPin, INPUT);

  // set all the other pins as outputs:
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  // set enablePin high so that motor can turn on:
  digitalWrite(enablePin, HIGH);
}

void reset() { //reset the state of the motors
  digitalWrite(enablePin, LOW); 
  digitalWrite(motor1Pin, LOW);
  digitalWrite(motor2Pin, LOW);
  digitalWrite(enablePin, HIGH);
}
void loop() {
  //  pinValue = digitalRead(switchPin);
  //  delay(1000);
  //set the speed of the motor
  analogWrite(enablePin, 255);

  Serial.println(pinValue);
  currSwitchState = digitalRead(switchPin);
  // check if the switch was flipped
  if (currSwitchState != prevSwitchState) {
    delay(60);
    currSwitchState = digitalRead(switchPin);
  }
  // if the switch is up, motor will turn clockwise:
  if (prevSwitchState == HIGH && currSwitchState == LOW) {
    reset();
    digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
    digitalWrite(motor2Pin, HIGH);  // set leg 2 of the H-bridge high
  }
  // if the switch is down, motor will turn counterclockwise:
  else if (prevSwitchState == LOW && currSwitchState == HIGH) {
    reset();
    digitalWrite(motor1Pin, HIGH);  // set leg 1 of the H-bridge high
    digitalWrite(motor2Pin, LOW);   // set leg 2 of the H-bridge low
  }
}

