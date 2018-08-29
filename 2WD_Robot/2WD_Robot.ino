#include <AFMotor.h>      //add Adafruit Motor Shield library
#include <Servo.h>

#define MAX_SPEED 160 // sets speed of DC traction motors to 150/250 or about 70% of full speed - to get power drain down.
#define MAX_SPEED_OFFSET 35 // this sets offset to allow for differences between the two DC traction motors

Servo RoboNeck; //the eye holder

AF_DCMotor rightMotor(1); // create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor leftMotor(4); // create motor #4, using M4 output on Motor Drive Shield, set to 1kHz PWM frequency


const unsigned short EchoPin = A4; // Echo pin for Ultrasonic sensor
const unsigned short TrigPin = A5; //Triger pin for Ultrasonic sensor



const unsigned short roboNeckPin = 9; //Servo input pin

int currentDist = 0; //
int speedSet = 0;
void setup() {
  Serial.begin(9600); //
  //Set the pins direction
  for (unsigned short i = 3; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(roboNeckPin, OUTPUT);

  RoboNeck.attach(roboNeckPin);

  RoboNeck.write(90); // tells the servo to position at 90-degrees ie. facing forward.

}

void loop() {
  currentDist = MeasuringDistance();
  if (currentDist > 20) {
    moveForward();
  }
  else if (currentDist < 10) {
    moveBackward();
  }
  else {
    changeDirection();
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

//
void moveForward() {
  rightMotor.run(FORWARD);      // turn right motor forward
  leftMotor.run(FORWARD);       // turn left motor forward
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    leftMotor.setSpeed(speedSet);
    rightMotor.setSpeed(speedSet);
    delay(5);
  }
}

//
void moveBackward() {
  Serial.print("The Robot is moving backward!!!");
  rightMotor.run(BACKWARD);      // turn right motor backward
  leftMotor.run(BACKWARD);       // turn left motor backward
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    leftMotor.setSpeed(speedSet);
    rightMotor.setSpeed(speedSet);
    delay(5);
  }
}

//
void changeDirection() {
  Stop();//

  RoboNeck.write(0);
  delay(1000);
  int leftDist = MeasuringDistance();   //
  delay(10);
  RoboNeck.write(180);
  delay(1000);
  int rightDist = MeasuringDistance();   //
  delay(10);
  RoboNeck.write(90); 
  if (leftDist < rightDist) {
    turnLeft();
  }
  else {
    turnRight();
  }
  return;
}

//
void Stop() {
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  //RoboNeck.write(70);  //
}

//
void turnLeft() {
  Serial.print("The Robot is turning left!!!");
  rightMotor.run(FORWARD);     // turn motor 4 forward
  leftMotor.run(BACKWARD);      // turn motor 2 backward
  leftMotor.setSpeed(speedSet + MAX_SPEED_OFFSET);
  delay(800); // run motors this way for 1500
  leftMotor.run(FORWARD);      // turn it on going forward
  rightMotor.run(FORWARD);     // turn it on going forward
  //Stop();
}

//
void turnRight() {
  Serial.print("The Robot is turning left!!!");
  rightMotor.run(BACKWARD);     // turn motor 4 forward
  leftMotor.run(FORWARD);      // turn motor 2 backward
  leftMotor.setSpeed(speedSet + MAX_SPEED_OFFSET);
  delay(800); // run motors this way for 1500
  leftMotor.run(FORWARD);      // turn it on going forward
  rightMotor.run(FORWARD);     // turn it on going forward
  //Stop();
}

