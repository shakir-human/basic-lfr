int STBY = 5;

int AIN1 = 3;
int AIN2 = 4;
int PWMA = 9;

int BIN1 = 11;
int BIN2 = 12;
int PWMB = 10;

const int threshold = 500;
void setup() {
  pinMode(STBY, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  
  digitalWrite(STBY, HIGH);  // disable standby
}

void forward() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  analogWrite(PWMB, 200);
  analogWrite(PWMA,200);
}
void right() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,LOW);
  analogWrite(PWMB, 0);
  analogWrite(PWMA,200);
}
void left() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  analogWrite(PWMB, 200);
  analogWrite(PWMA,0);
}
void back() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);
  analogWrite(PWMB, 200);
  analogWrite(PWMA, 200);
}

void stop() {
  analogWrite(PWMA,0);
  analogWrite(PWMB,0);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,LOW);
}

void loop() {
  int sensorValue1 = analogRead(A1);
  int sensorValue2 = analogRead(A2);
  int sensorValue3 = analogRead(A3);
  int sensorValue4 = analogRead(A4);
  int sensorValue5 = analogRead(A5);
  
  // Convert to 0 or 1 based on threshold
  int b1 = (sensorValue1 < threshold) ? 0 : 1;
  int b2 = (sensorValue2 < threshold) ? 0 : 1;
  int b3 = (sensorValue3 < threshold) ? 0 : 1;
  int b4 = (sensorValue4 < threshold) ? 0 : 1;
  int b5 = (sensorValue5 < threshold) ? 0 : 1;

  if(b2==1&&b4==1&&b3==0){
    forward();
  }
  else if(b2==0||b1==0){
    left();
    //delay(500);
  }
  else if(b4==0||b5==0){
    right();
    //delay(500);
  }
  else{
    stop();
  }

  delay(10);
}
