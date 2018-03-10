const int motor1Pin = 2;    // H-bridge leg 1 (pin 2)
const int switchPin = 3;    // switch input
const int motor2Pin = 4;    // H-bridge leg 2 (pin 7)
const int enablePin = 9;    // H-bridge enable pin
int pinValue;
int currSwitchState;
int prevSwitchState;
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
//In the main loop() read the switch. If it’s high, turn the motor one way by taking one H-bridge pin high and the other low. If the switch is low, reverse the direction by reversing the states of the two H-bridge pins.
void brake() { //reset the state of the motors
  digitalWrite(enablePin, LOW);
  digitalWrite(motor1Pin, LOW);
  digitalWrite(motor2Pin, LOW);
  digitalWrite(enablePin, HIGH);

}
void loop() {
  //  pinValue = digitalRead(switchPin);
  //  delay(1000);
  analogWrite(enablePin, 255);

  Serial.println(pinValue);
  currSwitchState = digitalRead(switchPin);
  // if the switch is low, motor will turn clockwise:
  if (currSwitchState != prevSwitchState) {
    delay(50);
    currSwitchState = 0;
    if (prevSwitchState = currSwitchState) {
      digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
      digitalWrite(motor2Pin, HIGH);  // set leg 2 of the H-bridge high
    }
  }
  // if the switch is high, motor will turn counterclockwise:
  else if (currSwitchState != prevSwitchState) {
    delay(600); //short delay
    currSwitchState = 1;
    if (prevSwitchState = currSwitchState) {
      digitalWrite(motor1Pin, HIGH);  // set leg 1 of the H-bridge high
      digitalWrite(motor2Pin, LOW);   // set leg 2 of the H-bridge low
    }
  }
  else {
    break();
  }
