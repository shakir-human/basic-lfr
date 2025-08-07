int STBY = 5;

int AIN1 = 3;
int AIN2 = 4;
int PWMA = 9;

int BIN1 = 11;
int BIN2 = 12;
int PWMB = 10;

void setup() {
  Serial.begin(9600);

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
  analogWrite(PWMB, 200);
  analogWrite(PWMA,200);
}
void left() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  analogWrite(PWMB, 200);
  analogWrite(PWMA,200);
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
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,LOW);
  analogWrite(PWMB, 0);
  analogWrite(PWMA, 0);
}

void loop() {
  forward();
  Serial.println("forward");
  delay(5000);
  stop();
  Serial.println("stop");
  delay(2000);
  back();
  Serial.println("back");
  delay(5000);
  stop();
  Serial.println("stop");
  delay(2000);
  right();
  Serial.println("right");
  delay(3000);
  stop();
  Serial.println("stop");
  delay(1000);
  left();
  Serial.println("left");
  delay(3000);
  stop();
  Serial.println("stop");
  delay(1000);
}
