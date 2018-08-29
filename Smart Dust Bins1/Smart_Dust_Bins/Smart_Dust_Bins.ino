#include <Servo.h>
#include <NewPing.h>
#define EchoPin 8
#define TrigPin 7
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.


NewPing UltraDist(TrigPin, EchoPin, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


int currentDist = 0;
Servo dustBin;
const unsigned short motorPin = 9;
 

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  dustBin.attach(motorPin);
}

void loop() {
  dustBin.write(180);
  currentDist = UltraDist.ping_cm();
  Serial.print("The Distance is: ");
  Serial.println(currentDist);
  if(currentDist < 20){
    Serial.println("Open");
    dustBin.write(90);
    delay(3000); 
    Serial.println("Close"); 
  }

  delay(50);
}



