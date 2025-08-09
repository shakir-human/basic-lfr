int STBY = 5;

int AIN1 = 3;
int AIN2 = 4;
int PWMA = 9;

int BIN1 = 11;
int BIN2 = 12;
int PWMB = 10;

const int threshold = 500;
const int numSensors = 5;
int sensorPins[numSensors] = {A1, A2, A3, A4, A5};
int weights[numSensors] = {-2, -1, 0, 1, 2};  // left -> right

int baseSpeed = 180;
float Kp = 255.0;            // start low when tuning
int lastCorrection = 0;
int maxCorrection = 255;    // clamp correction

void setup() {
  pinMode(STBY, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  digitalWrite(STBY, HIGH);
  Serial.begin(9600);
}

void setMotorSpeed(int leftSpeed, int rightSpeed) {
  if (leftSpeed >= 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, constrain(leftSpeed, 0, 255));
  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, constrain(-leftSpeed, 0, 255));
  }

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

void loop() {
  int sensorValues[numSensors];
  int weightedSum = 0;
  int sumValues = 0;

  // read sensors and binarize (1 = on line)
  for (int i = 0; i < numSensors; i++) {
    int val = analogRead(sensorPins[i]);
    sensorValues[i] = (val < threshold) ? 1 : 0; // adjust threshold per sensor
    weightedSum += sensorValues[i] * weights[i];
    sumValues += sensorValues[i];
  }

  if (sumValues == 0) {
    // line lost: continue last correction (helps recovery)
    int leftMotorSpeed = baseSpeed - lastCorrection;
    int rightMotorSpeed = baseSpeed + lastCorrection;
    leftMotorSpeed = constrain(leftMotorSpeed, 0, 255);
    rightMotorSpeed = constrain(rightMotorSpeed, 0, 255);
    setMotorSpeed(leftMotorSpeed, rightMotorSpeed);
    Serial.println("Line lost");
  } else {
    float position = (float)weightedSum / sumValues;         // the weighted average
    int correction = (int)(-Kp * position);                 // P control
    correction = constrain(correction, -maxCorrection, maxCorrection);
    lastCorrection = correction;

    int leftMotorSpeed = baseSpeed - correction;
    int rightMotorSpeed = baseSpeed + correction;
    leftMotorSpeed = constrain(leftMotorSpeed, 0, 255);
    rightMotorSpeed = constrain(rightMotorSpeed, 0, 255);

    setMotorSpeed(leftMotorSpeed, rightMotorSpeed);

    Serial.print("pos: "); Serial.print(position);
    Serial.print("  corr: "); Serial.print(correction);
    Serial.print("  L: "); Serial.print(leftMotorSpeed);
    Serial.print("  R: "); Serial.println(rightMotorSpeed);
  }

  delay(20); // 20 ms loop
}

