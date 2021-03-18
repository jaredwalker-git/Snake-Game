// MPU-6050 Short Example Sketch
//www.elegoo.com
//2016.12.9

#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t GyX,GyY;
int buzzer = 4;
int d = 0;
char ch;

void setup(){
  pinMode(buzzer, OUTPUT);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void buzz(){
   for(int i=0; i<60; i++){
    digitalWrite(buzzer, HIGH);
    delay(3);
    digitalWrite(buzzer, LOW);
    delay(3);
  }
}

void loop(){
  while(true){
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x43);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
    GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    if(Serial.available()){  
      ch = Serial.read();
    }
    if( ch == 'E' ){
      buzz();
      ch = 'O';
    }
    if( ch == 'R' ){
      d = 0;
      ch = 'O';
    }
    if( GyX > 20000 && GyY > 20000 ){
      continue;
    }
    if( GyX > 20000 && GyY < -20000 ){
      continue;
    }
    if( GyX < -20000 && GyY > 20000 ){
      continue;
    }
    if( GyX < -20000 && GyY < -20000 ){
      continue;
    }
    if( d != 1 ){
      if( GyX > 20000 ){
        Serial.print("down\n");
        d = 1;
      }
      if( GyX < -20000 ){
        Serial.print("up\n");
        d = 1;
      }
    }
    if( d != 2 ){
      if( GyY > 20000 ){
        Serial.print("right\n");
        d = 2;
      }
      if( GyY < -20000 ){
        Serial.print("left\n");
        d = 2;
      }
    }
  }
}
