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
int weights[numSensors] = {-2, -1, 0, 1, 2};

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

void forward() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  analogWrite(PWMB, 200);
  analogWrite(PWMA, 200);
}
void right() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,LOW);
  analogWrite(PWMB, 0);
  analogWrite(PWMA, 200);
}
void left() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  analogWrite(PWMB, 200);
  analogWrite(PWMA, 0);
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
  int weightedSum = 0;
  int sumValues = 0;

  // Read sensors
  for (int i = 0; i < numSensors; i++) {
    int val = analogRead(sensorPins[i]);
    int binaryVal = (val < threshold) ? 1 : 0; // Black=1, White=0
    weightedSum += binaryVal * weights[i];
    sumValues += binaryVal;
  }

  // If no sensors detect the line
  if (sumValues == 0) {
    stopMotors();
    Serial.println("Line lost!");
    return;
  }

  // Calculate position
  float position = (float)weightedSum / sumValues;
  Serial.print("Position: ");
  Serial.println(position);

  // Decision making
  if (position < -0.5) {
    left();
  } else if (position > 0.5) {
    right();
  } else {
    forward();
  }

  delay(20);
}