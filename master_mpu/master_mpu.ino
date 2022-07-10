#include <SoftwareSerial.h> 
#include <MPU9250_WE.h>
#include <Wire.h>
#define MPU9250_ADDR 0x68

MPU9250_WE myMPU9250 = MPU9250_WE(MPU9250_ADDR);

SoftwareSerial HC05(4,5);//블루투스 TX <-> 아두이노 4 연결  (마스터)

void setup() {
  HC05.begin(38400);
  Serial.begin(115200);
  Wire.begin();
  if(!myMPU9250.init()){
    Serial.println("MPU9250 does not respond");
  }
  else{
    Serial.println("MPU9250 is connected");
  }

  Serial.println("Position you MPU9250 flat and don't move it - calibrating...");
  delay(1000);
  myMPU9250.autoOffsets();
  Serial.println("Done!");
  myMPU9250.setAccRange(MPU9250_ACC_RANGE_2G);
  myMPU9250.enableAccDLPF(true);
  myMPU9250.setAccDLPF(MPU9250_DLPF_6);  
}

void loop() {
  xyzFloat gValue = myMPU9250.getGValues();
  xyzFloat angle = myMPU9250.getAngles();

  byte Myangle;

//  Serial.print("Angle x  = ");
//  Serial.print(angle.x);
//  Serial.print("  |  Angle y  = ");
//  Serial.print(angle.y);
//  Serial.print("  |  Angle z  = ");
//  Serial.println(angle.z);
//
//  Serial.print("Orientation of the module: ");
//  Serial.println(myMPU9250.getOrientationAsString());
//  Serial.println();

  if(50<=angle.z && angle.z<=90){
    HC05.write(100); //정지 flag 100 전송
  }
  else if(55<angle.y){
    Myangle = angle.y;
    HC05.write(Myangle); //전진 값 전송
  }
  else if(angle.y<=-35){
    Myangle = angle.y+90;
    HC05.write(Myangle); //후진 값 전송 (+90 보정)
  }
  else if(20<=angle.x){
    HC05.write(101); //우회전 flag 101 전송
  }
  else if(angle.x<=-75){
    HC05.write(102); //좌화전 flag 102 전송
  }
  else{
    HC05.write(100); //정지 flag 100 전송
  }
  
  delay(1000);
  
}
