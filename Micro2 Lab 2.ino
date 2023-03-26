#include "MPU6050.h"

#include "Wire.h"

MPU6050 mpu;

// pins
const int xAxis = A0; //X axis input pin
const int yAxis = A1; //Y axis input pin
int incomingByte = 0;
int joyX = 0; //Joystick x axis
int joyY = 0; //Joystick y axis

Vector normGyro;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Initialize the mpu
  if (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)) {
    while (1)
      yield();
  }

  mpu.calibrateGyro();


  // setup the IO pins
  pinMode(xAxis, INPUT);
  pinMode(yAxis, INPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    
    if(incomingByte == 'E') {
      // buzzer code
      tone(13, 500, 100);
      
    }
  }

  joyX = analogRead(xAxis);
  joyY = analogRead(yAxis);

   if(joyY > 700 ){
    Serial.print("W");
    delay(100);
  } else if(joyX < 200){
    Serial.print("A");
    delay(100);
  } else if(joyY < 200){
    Serial.print("S");
    delay(100);
  } else if(joyX > 700){
    Serial.print("D");
    delay(100);
  }


  normGyro = mpu.readNormalizeGyro();

  if( normGyro.YAxis > 100 ){
    Serial.print("W");
    delay(100);
  } else if(normGyro.XAxis < -200){
    Serial.print("A");
    delay(100);
  } else if(normGyro.YAxis < -100){
    Serial.print("S");
    delay(100);
  } else if(normGyro.XAxis > 200){
    Serial.print("D");
    delay(100);
  }
  



}