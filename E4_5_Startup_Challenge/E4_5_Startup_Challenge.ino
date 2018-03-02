//fsr is actually flex sensor for E5
int fsrPin= 0; //location of the fsr pin
int fsrValue; //value read from the analog pin
int lastFsrVal; //store the previous fsr value for comparison
int threshold = 120; //set threshold to a semi-high number 
int peakVal = 0; //st current peak value to 0

int led = 9; //red or warming led is connected to this pin
int ledValue; //corresponds to warming LED brightness
int led2 = 10; //blue or cooling led is connected to this pin
int ledValue2; //corresponds to cooling LED brightness

void setup() {
 // put your setup code here, to run once:
 Serial.begin(9600);
}

void warming(){ //fades in and out from min->max brightness, then max->min brightess
 for(ledValue=0; ledValue<=255; ledValue+=5){
   analogWrite(led, ledValue);
   delay(30);
   }

   for(ledValue=255;ledValue>=0; ledValue-=5){
     analogWrite(led, ledValue);
     delay(30);
     }
 }

void cooling(){ //blinking pattern with low brightness
 for(ledValue2=0; ledValue2<=100; ledValue2+=5){
   analogWrite(led2, ledValue2);
   delay(5);
   }
   delay(500);
   for(ledValue2=100;ledValue2>=0; ledValue2-=5){
     analogWrite(led2, ledValue2);
     delay(5);
     }
 }

void loop() {
   fsrValue = analogRead(fsrPin);
   Serial.println(fsrValue);  //value goes from 800+
   fsrValue = map(fsrValue, 700, 900, 0, 200); //map the value from fsrValue to a range of 0-200
   if(fsrValue >= threshold){ //when the read value is higher than threshold
    if (fsrValue > lastFsrVal){ //check if the current value is higher than the last measured fsr value
    peakVal = fsrValue; //change the peak value to the curent value
    }
    else if (peakVal >= threshold){
      //start the warming mechanism--pulse the LED in a breathe pattern
      warming();
    }
    peakVal = 0; //reset the peak value
   }
   lastFsrVal = fsrValue; //store the current fsr value for later
    
   if(fsrValue <= threshold){ //when the user is shifting around the seat
      if (fsrValue <= lastFsrVal){ //check if the current value is lower than the last value
        peakVal = fsrValue;       //set peak fsr value to current fsr value
      }
      else if (peakVal <= threshold){ //if the peak value is lower than the threshold
       //shifting around--constant low illuminance level in short flashes
       cooling();
      }
      peakVal - 0; //peak value resets
    }
    lastFsrVal - fsrValue; //temporarily store the fsr value
         
   delay(200); //short waiting time so arduino doesn't get spammed
}
