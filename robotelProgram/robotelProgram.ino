// --- Pin Definitions (Standard for Elegoo v4.0) ---
#define ENA 5    // Left Motor Speed
#define ENB 6    // Right Motor Speed
#define IN1 7    // Left Direction 1
#define IN2 8    // Left Direction 2
#define IN3 9    // Right Direction 1
#define IN4 11   // Right Direction 2
#define STBY 3   // Standby Pin

// --- Calibration Settings ---
int driveSpeed = 200;     // Speed (0-255)
int forwardTime = 2000;    // Time to move "a couple inches" (ms)
int turnTime = 500;       // Time to turn 90 degrees (ms) - Adjust this!

void setup() {
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(STBY, OUTPUT);
  
  // initialize the pushbutton pin as an input:
  //pinMode(buttonPin, INPUT_PULLUP);

  // Wait for the button to be pressed (LOW state indicates a press with INPUT_PULLUP)
  //while (digitalRead(buttonPin) == HIGH) {
    // This loop does nothing until the button is pressed
  //}
  digitalWrite(STBY, HIGH); // Enable motors
  moveForwardHalf();
  turnLeftAndForward();
  turnRightAndForward();
  turnRightAndForward();
  turnLeftAndForward();
  turnLeftAndForward();
  turnRightAndForward();
  turnRightAndForward();

}

void loop() {
  // Empty - sequence runs once on startup
}

// --- Movement Functions ---

void moveForwardHalf() {
  analogWrite(ENA, driveSpeed);
  analogWrite(ENB, driveSpeed);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, HIGH); // Left Forward
  digitalWrite(IN3, HIGH);  digitalWrite(IN4, HIGH); // Right Forward
  delay(forwardTime/2);  // Drive forward
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
  turnRight();
  moveForward();
}

void turnLeftAndForward () {
  turnLeft();
  moveForward();
}

void turnRight() {
  analogWrite(ENA, driveSpeed);
  analogWrite(ENB, driveSpeed);
  // To turn right: Left wheels forward, Right wheels backward
  digitalWrite(IN1, HIGH); digitalWrite(IN2, HIGH);  // Left Forward
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);  // Right Backward
  turnRight();
  delay(turnTime);// Execute turn
  stopCar();
  delay(500);
}

void turnLeft() {
  analogWrite(ENA, driveSpeed);
  analogWrite(ENB, driveSpeed);
  // To turn left: Left wheels backward, Right wheels forward
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);  
  digitalWrite(IN3, HIGH); digitalWrite(IN4, HIGH);
  turnLeft();
  delay(turnTime);// Execute turn
  stopCar();
  delay(500);
}

void stopCar() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}

// todos



