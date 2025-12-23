// --- Motor Pin Definitions for v4.0 (TB6612 Driver) ---
#define ENA 5    // Speed control for Left Motor
#define ENB 6    // Speed control for Right Motor
#define IN1 7    // Direction Left 1
#define IN2 8    // Direction Left 2
#define IN3 9    // Direction Right 1
#define IN4 11   // Direction Right 2
#define STBY 3   // Standby pin (Must be HIGH to move)

// --- Settings ---
int carSpeed = 150;     // Speed (0 to 255). 150 is a good starting point.
int moveDuration = 6000; // Time in milliseconds. 600ms is roughly 4-6 inches.

void setup() {
  // Set all pins as OUTPUT
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(STBY, OUTPUT);

  // Enable the motor driver
  digitalWrite(STBY, HIGH);

  // EXECUTE MOVEMENT ONCE
  moveForward();
  delay(moveDuration); // How long it drives
  stopCar();
}

void loop() {
  // We leave this empty so the car doesn't keep driving forever!
}

void moveForward() {
  // Set speeds
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);

  // Set Directions (If wheels spin backward, swap HIGH/LOW here)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

void stopCar() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}