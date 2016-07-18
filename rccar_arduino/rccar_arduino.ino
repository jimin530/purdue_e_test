#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(8, 9); // SoftwareSerial(TX, RX)
const byte BTpin = 3;
boolean BTconnected = false;

//모터A 컨트롤
int IN1=7;
int IN2=6;

//모터B 컨트롤
int IN3=5;
int IN4=4;

//모터A 스피드
int SPEED_R=11;

//모터B 스피드
int SPEED_L=10;

int now_speed=0;

char data;
String myString;

void setup() {
  // put your setup code here, to run once:
  BTSerial.begin(9600);
  Serial.begin(9600);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(BTpin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //for(pos = 0;pos <= 180;pos++)
  //{
  //  myservo.write(pos);
  //  delay(1);
  //}
  //for(pos = 180;pos >= 0; pos--)
  //{
  //  myservo.write(pos);
  //  delay(1);
  //}
  //Serial.println(digitalRead(STATE));
  //if(digitalRead(STATE)== HIGH)
  //{
  //  Serial.println("High");
  //}
  //else if(digitalRead(STATE)== LOW)
  //{
  //  Serial.println("Low");
  //}
  
  while(BTSerial.available()) {
     char data = (char)BTSerial.read();
     myString += data;
     delay(5);     
  }
  
  if(myString.equals("up\n")) {
     bothMotorStart();
     analogWrite(SPEED_R, now_speed);
     analogWrite(SPEED_L, now_speed);
     myString ="";
  }
  else if(myString.equals("down\n")) {
     bothMotorBack();
     analogWrite(SPEED_R, now_speed);
     analogWrite(SPEED_L, now_speed);
     myString ="";
  }
  else if(myString.equals("left\n")) {
     //turn();
     myString ="";
  }
  else if(myString.equals("right\n")) {
     //turn();
     myString ="";
  }
  else if(myString.equals("stop\n")) {
     stopAllMotor();
     myString ="";
  }
  else if(myString.equals("step1\n")) {
     now_speed=70;
     analogWrite(SPEED_R, now_speed);
     analogWrite(SPEED_L, now_speed);
     myString ="";
  }
  else if(myString.equals("step2\n")) {
     now_speed=120;
     analogWrite(SPEED_R, now_speed);
     analogWrite(SPEED_L, now_speed);
     myString ="";
  }
  else if(myString.equals("step3\n")) {
     now_speed=170;
     analogWrite(SPEED_R, now_speed);
     analogWrite(SPEED_L, now_speed);
     myString ="";
  }
  else if(myString.equals("step4\n")) {
     now_speed=220;
     analogWrite(SPEED_R, now_speed);
     analogWrite(SPEED_L, now_speed);
     myString ="";
  }
  else if(myString.equals("step5\n")) {
     now_speed=255;
     analogWrite(SPEED_R, now_speed);
     analogWrite(SPEED_L, now_speed);
     myString ="";
  }
}

//모터A,B 정회전
void bothMotorStart()
{
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
}

//모터A,B 역회전
void bothMotorBack()
{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
}
 
//모터A,B Stop
void stopAllMotor()
{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
}
 
//모터A 역회전, 모터B 정회전
void turnLeft()
{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
}
 
//모터A 정회전, 모터B 역회전
void turnRight()
{
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
}
 
//모터A 정회전, 모터B Stop
void motorA_Rotation()
{
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
}
 
//모터A Stop, 모터B 정회전
void motorB_Rotation()
{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
}
 
//모터A 역회전, 모터B Stop
void motorA_Reverse()
{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
}
 
//모터A Stop, 모터B 역회전
void motorB_Reverse()
{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
}
