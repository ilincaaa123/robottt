#include <MPU6050.h>
#include <Wire.h>
#include "I2Cdev.h"

MPU6050 mpu;

// --- Pin Definitions ---
#define ENA 5    // Left Motor Speed
#define ENB 6    // Right Motor Speed
#define IN1 7    // Left Direction 1
#define IN2 8    // Left Direction 2
#define IN3 9    // Right Direction 1
#define IN4 11   // Right Direction 2
#define STBY 3   // Standby Pin   

// --- Calibration Settings (From your todos) ---
int16_t acc_off_x = 386;
int16_t acc_off_y = 10;
int16_t acc_off_z = 789;
int16_t gyro_off_x = 39;
int16_t gyro_off_y = 109;
int16_t gyro_off_z = -58;

int driveSpeed = 25;   
int turnSpeed = 40; // Speed (0-255)
int halfForwardTime = 4610;
int forwardTime = 5680;   // Time to move "a couple inches" (ms)
int turnTime = 930;       // Time to turn 90 degrees (ms) - Adjust this!
int degreeAngle = 85;
const int bumpSensor = 2;

unsigned long lastTime;
float currentYaw = 0;

void setup() {
  Wire.begin();
  
  mpu.initialize();
  mpu.setXAccelOffset(acc_off_x);
  mpu.setYAccelOffset(acc_off_y);
  mpu.setZAccelOffset(acc_off_z);
  mpu.setXGyroOffset(gyro_off_x);
  mpu.setYGyroOffset(gyro_off_y);
  mpu.setZGyroOffset(gyro_off_z);

  pinMode(bumpSensor, INPUT_PULLUP);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH); 
  delay(500); // Give time to place the car down
}

void loop() {
  if (digitalRead(bumpSensor) == HIGH) {
    stopCar(); // Ensure motors are off
    delay(10);    // Stability delay
  }
  if (digitalRead(bumpSensor) == LOW) {
    moveForwardHalf();
    turnRightAndForward(); // Now measures a true 90 degrees
    while(true){
      turnLeftAndForward();
      turnLeftAndForward();
      turnLeftAndForward();
      turnLeftAndForward();
    }
  }
}

// --- Corrected Gyro Turning Functions ---

void turnLeftGyro() {
  currentYaw = 0; // Reset angle for this turn
  lastTime = millis();
  
  // Set motors to rotate left
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); 
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);

  while (abs(currentYaw) < degreeAngle) {
    updateYaw();
  }  
  
  stopCar();
  delay(500);
}

void turnRightGyro() {
  currentYaw = 0; 
  lastTime = millis();

  // Set motors to rotate right
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);

  while (abs(currentYaw) < degreeAngle) {
    updateYaw();
  }  
  
  stopCar();
  delay(500);
}

// Helper to calculate angle from gyro velocity
void updateYaw() {
  int16_t gz = mpu.getRotationZ();
  unsigned long currentTime = millis();
  float dt = (currentTime - lastTime) / 1000.0; // Delta time in seconds
  lastTime = currentTime;

  // Convert raw to degrees/sec (at default +/- 250 range, factor is 131.0)
  float gyroZrate = gz / 131.0;
  currentYaw += gyroZrate * dt;
}

void stopCar() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// Keep your moveForward functions here...
void moveForwardHalf() {
  analogWrite(ENA, driveSpeed);
  analogWrite(ENB, driveSpeed);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, HIGH); // Left Forward
  digitalWrite(IN3, HIGH);  digitalWrite(IN4, HIGH); // Right Forward
  delay(halfForwardTime);  // Drive forward
  stopCar();
  delay(500);}
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