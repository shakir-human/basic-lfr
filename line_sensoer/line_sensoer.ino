const int threshold = 500;  // adjust after calibration

void setup() {
  Serial.begin(9600);
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
  
  // print binary values
  Serial.print(b1);
  Serial.print("   ");
  Serial.print(b2);
  Serial.print("   ");
  Serial.print(b3);
  Serial.print("   ");
  Serial.print(b4);
  Serial.print("   ");
  Serial.println(b5);
  
  delay(50);
}
