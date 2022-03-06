#include <ezButton.h>

//Define switch states
#define SWITCH_OFF 0 
#define SWITCH_ON  1

ezButton button(2); 

//Define vairables and initial values
int switch_state = SWITCH_OFF; 
int speed1 = 250; 
int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;


void setup() {
  //Define inputs and outputs
  pinMode(3 ,OUTPUT);
  pinMode(4 ,OUTPUT);
  pinMode(5 ,OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(2 ,INPUT);
  
 button.setDebounceTime(50); // Set debounce time to 50 milliseconds

 //Calibrate phototransistor sensor
 while (millis() < 5000){
  sensorValue = analogRead(A0);
  if (sensorValue > sensorHigh){
    sensorHigh = sensorValue;
  }
  if(sensorValue < sensorLow){
    sensorLow = sensorValue;
  }
 }
}

void loop() {

  //Read sensor values from phototransistor
  sensorValue = analogRead(A0);
  // Map sensor values to integer values from 250 - 750 to determine tempo at which seqeunce is played 
  speed1 = map(sensorValue, sensorLow, sensorHigh, 250, 750); 
  button.loop();

  //Change switch state of button each time it is pressed
  if (button.isPressed()) {
    // change state of switch
    if (switch_state == SWITCH_OFF)
      switch_state = SWITCH_ON;
    else
      switch_state = SWITCH_OFF;
  }
  if (switch_state == SWITCH_OFF) {
  // When button not pressed, lights are off and no tone is played
  digitalWrite(3, LOW); 
  digitalWrite(4, LOW); 
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  }
else {

  //Play tones in sequence with LEDs matching, the speed at which this happens is determined by phototransistor sensor
  tone(8, 2200, speed1);
  digitalWrite(3, HIGH); 
  digitalWrite(4, LOW); 
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  delay(speed1);

  tone(8, 2640, speed1);
  digitalWrite(3, LOW); 
  digitalWrite(4, HIGH); 
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  delay(speed1);
  
  tone(8, 2530, speed1);
  digitalWrite(3, LOW); 
  digitalWrite(4, LOW); 
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  delay(speed1);
  
  tone(8, 2460, speed1);
  digitalWrite(3, LOW); 
  digitalWrite(4, LOW); 
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  delay(speed1); 
}  
}
