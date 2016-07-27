#include <Servo.h>

Servo myservo;//create a object of servo,named as myservo

#define LEFT_IR 4
#define RIGHT_IR 7

#define ENA_PIN   5 // ENA of DC motor driver module attach to pin5 of sunfounder uno board
#define ENB_PIN   6 // ENB of DC motor driver moduleattach to pin6 of sunfounder uno board
#define MOTOR_L_1 8 // left MOTOR_L_1 attach to pin8 
#define MOTOR_L_2 9 // left MOTOR_L_2 attach to pin9
#define MOTOR_R_1 10 //right  MOTOR_R_1 attach to pin10
#define MOTOR_R_2 11 //right MOTOR_R_2 attach to 

#define FORWARD 0  //define forward=0,car move forward
#define BACK    1 //define back=1,car move back
//#define SPEED 180 //define SPEED=180,it is the rotate speed of motor

#define ANGLE_RIGHT1  103 //define  ANGLE_RIGHT_MAX=130,it is the  rotate angle of servo 
#define ANGLE_RIGHT2 113
#define ANGLE_RIGHT3  123
#define ANGLE_LEFT1   83
#define ANGLE_LEFT2  73
#define ANGLE_LEFT3  63
#define ANGLE_MIDDLE 93

int SPEED = 180;
boolean isForward = true;
boolean isStop = true;
boolean isFinish = false;

int BACK_LEFT_UL_TRIG = A4;
int BACK_LEFT_UL_ECHO = A5;
int BACK_RIGHT_UL_TRIG = A2;
int BACK_RIGHT_UL_ECHO = A3;
int FRONT_UL_TRIG = A0;
int FRONT_UL_ECHO = A1;

int LED = 13;
unsigned char angle = ANGLE_MIDDLE;
char getstr;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);

  pinMode(BACK_LEFT_UL_TRIG, OUTPUT);
  pinMode(BACK_LEFT_UL_ECHO, INPUT);
  pinMode(BACK_RIGHT_UL_TRIG, OUTPUT);
  pinMode(BACK_RIGHT_UL_ECHO, INPUT);
  pinMode(FRONT_UL_TRIG, OUTPUT);
  pinMode(FRONT_UL_ECHO, INPUT);

  pinMode(LEFT_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);

  pinMode(ENA_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);
  pinMode(MOTOR_L_1, OUTPUT);
  pinMode(MOTOR_L_2, OUTPUT);
  pinMode(MOTOR_R_1, OUTPUT);
  pinMode(MOTOR_R_2, OUTPUT);

  myservo.attach(2);//servo attach to pin2
  myservo.write(ANGLE_MIDDLE);//set the angle(90) of servo

  CAR_move(BACK, 0, 0); //car stop

}

void loop() {
  // put your main code here, to run repeatedly:
  getstr = Serial.read();

  //print_Front_Distance();
  //print_Back_Left_Distance();
  //print_Back_Right_Distance();
  //delay(300);
  if (!isFinish)
  {
    CAR_move(BACK, SPEED, SPEED);
    delay(150);
    CAR_stop();
    if (isHorizontal())
    {
      CAR_stop();
      isFinish = true;
    }
    delay(500);
  }

  /*
    //전진
    if (getstr == 'a') {
    CAR_move(FORWARD, SPEED, SPEED); //car move forward with speed 180
    }

    //후진
    else if (getstr == 'b') {
    CAR_move(BACK, SPEED, SPEED);
    }

    //정지
    else if (getstr == 'c') {
    CAR_stop();
    }

    else if (getstr == 'd') {
    SPEED = 120;
    if (isForward && !isStop)
    {
      CAR_move(FORWARD, SPEED, SPEED);
    }
    else if (!isForward && !isStop)
    {
      CAR_move(BACK, SPEED, SPEED);
    }
    }

    else if (getstr == 'e') {
    SPEED = 135;
    if (isForward && !isStop)
    {
      CAR_move(FORWARD, SPEED, SPEED);
    }
    else if (!isForward && !isStop)
    {
      CAR_move(BACK, SPEED, SPEED);
    }
    }

    else if (getstr == 'f') {
    SPEED = 170;
    if (isForward && !isStop)
    {
      CAR_move(FORWARD, SPEED, SPEED);
    }
    else if (!isForward && !isStop)
    {
      CAR_move(BACK, SPEED, SPEED);
    }
    }

    else if (getstr == 'g') {
    SPEED = 215;
    if (isForward && !isStop)
    {
      CAR_move(FORWARD, SPEED, SPEED);
    }
    else if (!isForward && !isStop)
    {
      CAR_move(BACK, SPEED, SPEED);
    }
    }

    else if (getstr == 'h') {
    SPEED = 250;
    if (isForward && !isStop)
    {
      CAR_move(FORWARD, SPEED, SPEED);
    }
    else if (!isForward && !isStop)
    {
      CAR_move(BACK, SPEED, SPEED);
    }
    }

    //방향 중간
    else if (getstr == 'i') {
    angle = ANGLE_MIDDLE;//servo rotate to 130
    myservo.write(angle);
    }

    //왼쪽 1번
    else if (getstr == 'j') {
    angle = ANGLE_LEFT1;//servo rotate to 130
    myservo.write(angle);
    }

    //왼쪽 2번
    else if (getstr == 'k') {
    angle = ANGLE_LEFT2;//servo rotate to 130
    myservo.write(angle);
    }

    //왼쪽 3번
    else if (getstr == 'l') {
    angle = ANGLE_LEFT3;//servo rotate to 130
    myservo.write(angle);
    }

    //오른쪽 1번
    else if (getstr == 'm') {
    angle = ANGLE_RIGHT1;//servo rotate to 130
    myservo.write(angle);
    }

    //오른쪽 2번
    else if (getstr == 'n') {
    angle = ANGLE_RIGHT2;//servo rotate to 130
    myservo.write(angle);

    }

    //오른쪽 3번
    else if (getstr == 'o') {
    angle = ANGLE_RIGHT3;//servo rotate to 130
    myservo.write(angle);
    }*/
}

/**
   IR 이용 함수
*/
boolean isHorizontal() //둘다 가까운상태면(수평) true반환(IR센서 이용)
{
  int val_left = digitalRead(LEFT_IR);
  int val_right = digitalRead(RIGHT_IR);
  if (val_left == val_right && val_right == LOW) //둘다 가까운상태면(수평)
  {
    return true;
  }
  return false;
}

boolean isNear(int pinnum) //가까이 있으면 true반환(IR센서 이용)
{
  int val = digitalRead(pinnum);
  if (val == LOW) //가까이 있으면
  {
    return true;
  }
  return false;
}

/**
   초음파 이용 함수
*/
void print_Front_Distance()
{
  Serial.print("FRONT : ");
  Serial.print(getDistance(FRONT_UL_TRIG, FRONT_UL_ECHO));
  Serial.println("cm");
}

void print_Back_Left_Distance()
{
  Serial.print("BACK_LEFT : ");
  Serial.print(getDistance(BACK_LEFT_UL_TRIG, BACK_LEFT_UL_ECHO));
  Serial.println("cm");
}

void print_Back_Right_Distance()
{
  Serial.print("BACK_RIGHT : ");
  Serial.print(getDistance(BACK_RIGHT_UL_TRIG, BACK_RIGHT_UL_ECHO));
  Serial.println("cm");
}

int getDistance(int trig, int echo)
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  int distance = pulseIn(echo, HIGH) * 17 / 1000;

  return distance;
}

/**
   서보
*/
void SERVO_Write(void)
{
  myservo.write(angle);//set the rotate angle of servo
}

void CAR_move(unsigned char direction, unsigned char speed_left, unsigned char speed_right)
{
  switch (direction)
  {
    //car move forward with speed 180
    case 0:
      digitalWrite(MOTOR_L_1, HIGH);
      digitalWrite(MOTOR_L_2, LOW); //left motor clockwise rotation
      digitalWrite(MOTOR_R_1, HIGH);
      digitalWrite(MOTOR_R_2, LOW);
      isForward = true;
      isStop = false;
      break;//right motor clockwise rotation
    //car move back with speed 180
    case 1:
      digitalWrite(MOTOR_L_1, LOW);
      digitalWrite(MOTOR_L_2, HIGH);
      digitalWrite(MOTOR_R_1, LOW);
      digitalWrite(MOTOR_R_2, HIGH);
      isForward = false;
      isStop = false;
      break;
    default:
      break;
  }
  analogWrite(ENA_PIN, speed_left); //write speed_left to ENA_PIN,if speed_left is high,allow left motor rotate
  analogWrite(ENB_PIN, speed_right); //write speed_right to ENB_PIN,if speed_right is high,allow right motor rotate
}

void CAR_stop()
{
  digitalWrite(MOTOR_L_1, LOW);
  digitalWrite(MOTOR_L_2, LOW);
  digitalWrite(MOTOR_R_1, LOW);
  digitalWrite(MOTOR_R_2, LOW);
  isStop = true;
}

