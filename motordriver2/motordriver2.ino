// === Motor Driver Pins ===
int STBY = 5;

int AIN1 = 3;
int AIN2 = 4;
int PWMA = 9;

int BIN1 = 11;
int BIN2 = 12;
int PWMB = 10;

// === Universal Motor Control Function ===
void setMotor(int pin1, int pin2, int pwm, int speed) {
  if (speed > 0) {              // Forward
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
  } else if (speed < 0) {       // Backward
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    speed = -speed;             // Make speed positive for PWM
  } else {                      // Stop
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
  analogWrite(pwm, constrain(speed, 0, 255));
}

void setup() {
  pinMode(STBY, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  digitalWrite(STBY, HIGH); // Enable driver
}

void loop() {
  // Forward
  setMotor(AIN1, AIN2, PWMA, 150);
  setMotor(BIN1, BIN2, PWMB, 150);
  delay(2000);

  // Backward
  setMotor(AIN1, AIN2, PWMA, -150);
  setMotor(BIN1, BIN2, PWMB, -150);
  delay(2000);

  // Left turn (left motor backward, right forward)
  setMotor(AIN1, AIN2, PWMA, -150);
  setMotor(BIN1, BIN2, PWMB, 150);
  delay(1500);

  // Right turn (left motor forward, right backward)
  setMotor(AIN1, AIN2, PWMA, 150);
  setMotor(BIN1, BIN2, PWMB, -150);
  delay(1500);

  // Stop
  setMotor(AIN1, AIN2, PWMA, 0);
  setMotor(BIN1, BIN2, PWMB, 0);
  delay(2000);
}


