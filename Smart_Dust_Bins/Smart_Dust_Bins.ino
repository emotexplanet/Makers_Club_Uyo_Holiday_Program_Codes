#include <Servo.h>
#define EchoPin 10
#define TrigPin 11

int currentDist = 0;
Servo dustBin;
 

void setup() {
  Serial.begin(9600);
  dustBin.attach(9);
}

void loop() {
  dustBin.write(180);
  currentDist = MeasuringDistance();
  Serial.print("THe Distance is: ");
  Serial.println(currentDist);
  if(currentDist < 20){
    Serial.println("Open");
    dustBin.write(90);
    delay(5000); 
    Serial.println("Close"); 
  }

  if(currentDist > 200){
    currentDist = 200;
  }
}


//Measure the distance
int MeasuringDistance() {
  long duration;
  pinMode(TrigPin, OUTPUT);
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  pinMode(EchoPin, INPUT);
  duration = pulseIn(EchoPin, HIGH);
  int distance = duration / 58;
  return distance;
}
