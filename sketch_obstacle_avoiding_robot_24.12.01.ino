#include <AFMotor.h>

int pos = 0;

// this constant won't change. It's the pin number of the sensor's output:
#define MAX_SPEED 190
#define TURN_SPEED 100
#define MAX_DISTANCE 25
const int pingPin = 2;
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

void setup() {
// initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  

 int distance = microsecondsToCentimeters(duration);
  if (distance <= MAX_DISTANCE) {
    stopMotors();
    delay(1000);  // Introduce a delay after stopping motors to prevent immediate reaction

    // Turn the robot if an obstacle is too close
    Serial.println("Obstacle detected! Turning Left...");
    turnLeft();
    delay(1500); // Delay to ensure the turn is completed
    stopMotors();
    delay(500); // Add delay after turning before checking again
  } else {
    moveForward(); // Move forward if no obstacles are detected
    Serial.println("Moving forward..."); // Print to monitor movement
  }
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

// Motor control functions
void moveForward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);

  motor1.setSpeed(MAX_SPEED);
  motor2.setSpeed(MAX_SPEED);
  motor3.setSpeed(MAX_SPEED);
  motor4.setSpeed(MAX_SPEED);
}

void stopMotors() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void turnRight() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);

  motor1.setSpeed(TURN_SPEED);
  motor2.setSpeed(TURN_SPEED);
  motor3.setSpeed(TURN_SPEED);
  motor4.setSpeed(TURN_SPEED);
}

void turnLeft() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(FORWARD);
  motor4.run(FORWARD);

  motor1.setSpeed(MAX_SPEED);
  motor2.setSpeed(MAX_SPEED);
  motor3.setSpeed(MAX_SPEED);
  motor4.setSpeed(MAX_SPEED);
}
