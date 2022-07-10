#include <SoftwareSerial.h> //시리얼통신 라이브러리 호출

//핀번호
#define ENA 10
#define ENB 5
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6
#define LED 11

#define blueTx 2   //Tx (보내는핀 설정)at
#define blueRx 3   //Rx (받는핀 설정)
SoftwareSerial HC06(blueTx, blueRx);  //블루투스 TX <-> 아두이노 2 연결 (슬레이브)


//자동차 제어 함수
void Go(byte speed);
void Back(byte speed);
void Stop();
void LeftGo();
void rightGo();

void setup() {
  Serial.begin(9600);  //시리얼모니터 사용
  HC06.begin(9600); //블루투스 시리얼
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(LED,OUTPUT);
  
}

void loop() {
  
   if(HC06.available()){  //블루투스에서 데이터가 들어오면
    
    byte in_data;         // 블루투스로 입력된 데이터 저장을 위한 변수
    in_data = HC06.read();  //블루투스로 입력된 데이터 in_data에 저장
    Serial.println(in_data);

    //GYRO 센서 에서 들어온 값에 비례하게 Speed 조절하기 위해서 범위 변환
    if (in_data == 100 ) {        //  정지
      Stop();
    }else if (in_data == 101 ) {  // 우회전
      rightGo();
    }else if (in_data == 102) {   // 좌회전
      LeftGo();
    }else if (in_data > 55){      //  전진 55~90 값 들어옴
      Go(in_data+165);
    }else if (in_data <= 55){     // 후진 0~55값 들어옴
      Back(200-in_data);
    }else {
      Stop();
    }

    
//    if(0<=in_data && in_data<=6){
//      Back((in_data-6) * (-36));
//    }
//    else if(in_data == 7){
//      LeftGo();
//    }
//    else if(in_data == 8){
//     rightGo();
//    }
//    else if(17<=in_data && in_data<=36){
//      Go(13 * (in_data-17));
//    }
//    else if(in_data == 9){
//      Stop();
//    }
//    else{
//      Stop();
//    }
    
   
  }

}


void Go(byte speed){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);   
      analogWrite(ENA, speed);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);   
      analogWrite(ENB, speed);
      digitalWrite(LED,HIGH);
}

void Back(byte speed){
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);   
      analogWrite(ENA, speed);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);  
      analogWrite(ENB, speed);
      digitalWrite(LED,HIGH);
}

void Stop(){
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
      digitalWrite(LED,LOW);
}
//좌회전 -> A 가 빨라야함
void LeftGo(){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);   
      analogWrite(ENA,255);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW); 
      analogWrite(ENB, 150);
      digitalWrite(LED,HIGH);
}
//우회전  -> B 가 빨라야함
void rightGo(){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);  
      analogWrite(ENA, 150);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);   
      analogWrite(ENB, 255);
      digitalWrite(LED,HIGH);
}
