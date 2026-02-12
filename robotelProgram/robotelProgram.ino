#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

// --- Pin Definitions (Standard for Elegoo v4.0) ---
#define ENA 5    // Left Motor Speed
#define ENB 6    // Right Motor Speed
#define IN1 7    // Left Direction 1
#define IN2 8    // Left Direction 2
#define IN3 9    // Right Direction 1
#define IN4 11   // Right Direction 2
#define STBY 3   // Standby Pin
// --- Calibration Settings ---
int driveSpeed = 25;   
int turnSpeed = 40; // Speed (0-255)
int halfForwardTime = 4610;
int forwardTime = 5680;   // Time to move "a couple inches" (ms)
int turnTime = 930;       // Time to turn 90 degrees (ms) - Adjust this!
int degreeAngle = 82;
const int bumpSensor = 2;
bool hasStarted = false;

void setup() {

  Wire.begin();
  mpu6050.begin();

  mpu6050.calcGyroOffsets(true) ;

  pinMode(bumpSensor, INPUT_PULLUP);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH); // Enable motors
  
  delay(500); // Short pause before it takes off

}

void loop() {
  
  if (digitalRead(bumpSensor) == HIGH) {
    stopCar(); // Ensure motors are off
    delay(10);    // Stability delay
  }

  if (digitalRead(bumpSensor) == LOW) {
    moveForwardHalf();
    turnRightAndForward();
    while(true){
      turnLeftAndForward();
      turnLeftAndForward();
      turnLeftAndForward();
      turnLeftAndForward();
    }
  }
}

// --- Movement Functions ---

void turnLeftGyro(){
  
  mpu6050.update();
  float startAngle = mpu6050.getAngleZ();

  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  // Left Forward
  
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);  // Right Backward

  analogWrite(ENA, turnSpeed);

  analogWrite(ENB, turnSpeed);

  float currentAngle = startAngle;

  while (abs(currentAngle - startAngle) < degreeAngle) {
    mpu6050.update();
    currentAngle = mpu6050.getAngleZ();
  }  
  
  stopCar();
  delay(500);
}


void turnRightGyro(){
  mpu6050.update();
  float startAngle = mpu6050.getAngleZ();

  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);  // Left Forward
  
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  // Right Backward

  analogWrite(ENA, turnSpeed);

  analogWrite(ENB, turnSpeed);

  float currentAngle = startAngle;

  while (abs(currentAngle - startAngle) < degreeAngle) {
    mpu6050.update();
    currentAngle = mpu6050.getAngleZ();
  }  
  
  stopCar();
  delay(500);
}


void moveForwardHalf() {
  analogWrite(ENA, driveSpeed);
  analogWrite(ENB, driveSpeed);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, HIGH); // Left Forward
  digitalWrite(IN3, HIGH);  digitalWrite(IN4, HIGH); // Right Forward
  delay(halfForwardTime);  // Drive forward
  stopCar();
  delay(500);         // Short pause
}
void moveForward() {
  analogWrite(ENA, driveSpeed);
  analogWrite(ENB, driveSpeed);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, HIGH); // Left Forward
  digitalWrite(IN3, HIGH);  digitalWrite(IN4, HIGH); // Right Forward
  delay(forwardTime);  // Drive forward
  stopCar();
  delay(500);         // Short pause
}

void turnRightAndForward() {
  turnRightGyro();
  moveForward();
}

void turnLeftAndForward () {
  turnLeftGyro();
  moveForward();
}

void turnRight() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);  // Left Forward
  
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  // Right Backward

  analogWrite(ENA, turnSpeed);

  analogWrite(ENB, turnSpeed);

  delay(turnTime);// Execute turn
  stopCar();
  delay(500);
}

void turnLeft() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  // Left Forward
  
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);  // Right Backward

  analogWrite(ENA, turnSpeed);

  analogWrite(ENB, turnSpeed);

  delay(turnTime);// Execute turn
  stopCar();
  delay(500);
}

void stopCar() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}

// todos



