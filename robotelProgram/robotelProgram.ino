// --- Pin Definitions (Standard for Elegoo v4.0) ---
#define ENA 5    // Left Motor Speed
#define ENB 6    // Right Motor Speed
#define IN1 7    // Left Direction 1
#define IN2 8    // Left Direction 2
#define IN3 9    // Right Direction 1
#define IN4 11   // Right Direction 2
#define STBY 3   // Standby Pin

// --- Calibration Settings ---
int driveSpeed = 50;     // Speed (0-255)
int forwardTime = 1000;    // Time to move "a couple inches" (ms)
int turnTime = 900;       // Time to turn 90 degrees (ms) - Adjust this!

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

  delay(2000);        // Wait 2 seconds so you can put it on the floor

  turnRight();
  delay(turnTime);     // Execute turn

  stopCar(); 
  //moveForwardHalf();
  //turnLeftAndForward();
  /*turnRightAndForward();
  turnRightAndForward();
  turnLeftAndForward();
  turnLeftAndForward();
  turnRightAndForward();
  turnRightAndForward();
  */
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
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);  // Left Forward
  
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  // Right Backward

  analogWrite(ENA, driveSpeed);

  analogWrite(ENB, driveSpeed);

  delay(turnTime);// Execute turn
  stopCar();
}

void turnLeft() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  // Left Forward
  
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);  // Right Backward

  analogWrite(ENA, driveSpeed);

  analogWrite(ENB, driveSpeed);

  delay(turnTime);// Execute turn
  stopCar();
}

void stopCar() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}

// todos



