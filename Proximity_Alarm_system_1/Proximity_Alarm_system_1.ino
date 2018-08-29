/*
 * Arduino Alarm system (sound alarm when some go close to the device)
 * Ultrasonic sensor
 *  Trigger => 3
 *  Echo    => 4
 * Piezo    => 8
 * 
 */
int TrigPin = 3; //Trigger pin of the ultrasonic sensor
int EchoPin = 4;//Echo pin of the ultrasonic sensor
int piezoPin = 8; //piezo pin for sound
const int AlamDistance = 100;
int currentDist = 0; //
void setup() {
  Serial.begin(9600);
}
void loop() {
  currentDist = MeasuringDistance();
  if (currentDist < AlamDistance) {
    digitalWrite(piezoPin, HIGH);
  }
  else{
    digitalWrite(piezoPin, LOW);
  }
  delay(100);
}
//Measure the distance
int MeasuringDistance() {
//  pinMode(Trig, OUTPUT);
//  pinMode(Echo, INPUT);
//  digitalWrite(Trig, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(Trig, LOW);
//  delayMicroseconds(2);
//  digitalWrite(Trig, HIGH);
//  long duration = pulseIn(Echo, HIGH); //Get time
//  /*distance = (time*speed of sound in Air (340m/s))/2
//   *PulseIn(), gives results in microseconds.
//   *This has to be converted to seconds,
//   *therefore divide by 1,000,000 (1s = 1000000us).
//   *We are measuring the distance in Cm instead of M
//   *Therefore, we multiply by 100 (1m = 100cm)
//   *(340/2)/(1000000)*(100) = 340/20000
//   */ 
//  int distance = duration*340/20000; //Calculate the distance
//  Serial.print(distance);
//  Serial.println("Cm");
//  return distance;

long duration;
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  duration = pulseIn(EchoPin, HIGH);
  int distance = duration / 58;
  return distance;
  //The set is for build extended distance measurement
 }
