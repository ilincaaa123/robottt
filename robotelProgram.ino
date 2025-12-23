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
int turnTime = 3000;       // Time to turn 90 degrees (ms) - Adjust this!

void setup() {
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(STBY, OUTPUT);
  
  digitalWrite(STBY, HIGH); // Enable motors

  // --- SEQUENCE ---
  delay(2000);        // Wait 2 seconds so you can put it on the floor
  
  moveForward();
  delay(forwardTime);  // Drive forward
  
  /* stopCar();
  delay(500);         // Short pause
  
  turnRight();
  delay(turnTime);     // Execute turn
  */
  stopCar();          // Final stop
}

void loop() {
  // Empty - sequence runs once on startup
}

// --- Movement Functions ---

void moveForward() {
  analogWrite(ENA, driveSpeed);
  analogWrite(ENB, driveSpeed);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, HIGH); // Left Forward
  digitalWrite(IN3, HIGH);  digitalWrite(IN4, HIGH); // Right Forward
}

void turnRight() {
  analogWrite(ENA, driveSpeed);
  analogWrite(ENB, driveSpeed);
  // To turn right: Left wheels forward, Right wheels backward
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  // Left Forward
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  // Right Backward
}

void stopCar() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}



