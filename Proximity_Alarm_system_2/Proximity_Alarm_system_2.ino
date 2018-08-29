/*
 * Arduino Alarm system (sound alarm when some go close to the device)
 * PIR Motion Sensor => 3
 * Piezo    => 8
 * 
 */

int piezoPin = 8; //piezo pin for sound
int PIR_Motion_Pin = 3; //PIR Motion Sensor pin for detecting motion

void setup() {
  Serial.begin(9600); //Set up serial monitor
  pinMode(PIR_Motion_Pin, INPUT); //set the pin direction to input
}

void loop() {
  int motion = digitalRead(PIR_Motion_Pin);//read the status of the pin
  if (motion == 1) {
    digitalWrite(piezoPin, HIGH);
  }
  else{
    digitalWrite(piezoPin, LOW);
  }
  delay(10); //Delay for 1 second
}

