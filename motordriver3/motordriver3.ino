// TB6612FNG Pinout for Arduino Nano
int STBY = 5;  // Standby

// Motor A (Left Motor)
int AIN1 = 3;
int AIN2 = 4;
int PWMA = 9; // PWM pin

// Motor B (Right Motor)
int BIN1 = 11;
int BIN2 = 12;
int PWMB = 10; // PWM pin

void setup() {
  pinMode(STBY, OUTPUT);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  digitalWrite(STBY, HIGH); // Enable motor driver
  Serial.begin(9600);
}

void setMotorSpeed(int leftSpeed, int rightSpeed) {
  // LEFT MOTOR
  if (leftSpeed >= 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, constrain(leftSpeed, 0, 255));
  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, constrain(-leftSpeed, 0, 255));
  }

  // RIGHT MOTOR
  if (rightSpeed >= 0) {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    analogWrite(PWMB, constrain(rightSpeed, 0, 255));
  } else {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    analogWrite(PWMB, constrain(-rightSpeed, 0, 255));
  }
}

void stopMotors() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}

void loop() {
  Serial.println("Forward");
  setMotorSpeed(150, 150); // Forward
  delay(2000);

  Serial.println("Backward");
  setMotorSpeed(-150, -150); // Backward
  delay(2000);

  Serial.println("Turn Left");
  setMotorSpeed(-100, 100); // Left turn
  delay(2000);

  Serial.println("Turn Right");
  setMotorSpeed(100, -100); // Right turn
  delay(2000);

  Serial.println("Stop");
  stopMotors();
  delay(2000);
}
