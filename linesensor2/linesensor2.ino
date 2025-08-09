const int threshold = 500;//since 0 is black and 900smth is white atleast in my sensoer so midd is 500;-;
const int sensorpins[5] ={A1,A2,A3,A4,A5}; //pins for the sensor in the nano
int sensorvalue[5];// takes the analog value
int binaryvalue[5];//takes the converted 0,1 value from analog value

void setup(){
  Serial.begin(9600);
}

void loop(){
  for(int i = 0; i < 5; i++){
    sensorvalue[i]=analogRead(sensorpins[i]);
    binaryvalue[i] = (sensorvalue[i] > threshold) ? 1 : 0;
  }

  for(int i = 0; i < 5; i++){
    Serial.print(binaryvalue[i]);
    Serial.print(" ");
  }
  Serial.println();

}



