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
int turnSpeed = 50; // Speed (0-255)
int halfForwardTime = 4600;
int forwardTime = 5650;   // Time to move "a couple inches" (ms)
int turnTime = 878;       // Time to turn 90 degrees (ms) - Adjust this!
const int bumpSensor = 2;
bool hasStarted = false;

void setup() {
  pinMode(bumpSensor, INPUT_PULLUP);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH); // Enable motors
  

  
  delay(500); // Short pause before it takes off

  // initialize the pushbutton pin as an input:
  //pinMode(buttonPin, INPUT_PULLUP);

  // Wait for the button to be pressed (LOW state indicates a press with INPUT_PULLUP)
  //while (digitalRead(buttonPin) == HIGH) {
    // This loop does nothing until the button is pressed
  //}

  //delay(2000);        // Wait 2 seconds so you can put it on the floor
    /*moveForwardHalf();
    turnRightAndForward();
    while(true){
      turnLeftAndForward();
      turnLeftAndForward();
      turnLeftAndForward();
      turnLeftAndForward();
    
    }*/
    

  //turnLeftAndForward();
  //turnLeftAndForward();
  //turnRightAndForward();
  //turnRightAndForward();

    //stopCar(); 
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



