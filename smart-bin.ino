#include <Servo.h>
Servo myServo;

#define TRIG_PIN D5    
#define ECHO_PIN D6     
#define SERVO_PIN D7    

long duration;
int distance;
const int DISTANCE_THRESHOLD = 15; 

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(0);
  delay(1000);
}

void loop() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH, 30000); 

  if (duration == 0) {
    Serial.println("No echo detected!");
    return;
  }
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance < DISTANCE_THRESHOLD) {
    Serial.println("Object detected!");
    myServo.write(90);
    delay(2000);      
    myServo.write(0);
    delay(1000);       
  }
  delay(200);
}