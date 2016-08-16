#include <Servo.h>

Servo myservo;

int LEFT_IR = 4;
int RIGHT_IR = 7;

int ENA_PIN = 5;
int ENB_PIN = 6;
int MOTOR_L_1 = 8; 
int MOTOR_L_2 = 9;
int MOTOR_R_1 = 10;
int MOTOR_R_2 = 11; 

int FORWARD = 0;
int BACK = 1;

int ANGLE_RIGHT1 = 101;
int ANGLE_RIGHT2 = 111;
int ANGLE_RIGHT3 = 121;
int ANGLE_LEFT1 = 81;
int ANGLE_LEFT2 = 71;
int ANGLE_LEFT3 = 61;
int ANGLE_MIDDLE = 91;

int MOVETIME = 150;

int REARAREA = 20;
int REARGAP = 5;

int PARALLELAREA = 25;
int PARALLELGAP = 13;

int SPEED = 180;
boolean isForward = true;
boolean isStop = true;
boolean isParking_Finish = false;

int LEFT_TRIG = A4;
int LEFT_ECHO = A5;
int RIGHT_TRIG = A2;
int RIGHT_ECHO = A3;

int LED = 13;
unsigned char angle = ANGLE_MIDDLE;
char getstr;

int flag = 0;

boolean isNear(int pinnum)
{
  int val = digitalRead(pinnum);
  if (val == LOW)
  {
    return true;
  }
  return false;
}

boolean isHorizontal()
{
  int val_left = digitalRead(LEFT_IR);
  int val_right = digitalRead(RIGHT_IR);
  if (val_left == LOW && val_right == LOW)
  {
    return true;
  }
  return false;
}

int getDistance(int trig, int echo)
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(20);
  digitalWrite(trig, LOW);
  return pulseIn(echo, HIGH);
}

int getLeft()
{
  digitalWrite(LEFT_TRIG, HIGH);
  delayMicroseconds(20);
  digitalWrite(LEFT_TRIG, LOW);
  return pulseIn(LEFT_ECHO, HIGH);
}

int getRight()
{
  digitalWrite(RIGHT_TRIG, HIGH);
  delayMicroseconds(20);
  digitalWrite(RIGHT_TRIG, LOW);
  return pulseIn(RIGHT_ECHO, HIGH);
}

void setMiddle()
{
    angle = ANGLE_MIDDLE;
    myservo.write(angle);
    delay(MOVETIME);  
}

void setRight()
{
    angle = ANGLE_RIGHT3;
    myservo.write(angle);
    delay(MOVETIME);  
}

void setLeft()
{
    angle = ANGLE_LEFT3;
    myservo.write(angle);
    delay(MOVETIME);  
}

void CAR_move(unsigned char direction, unsigned char speed_left, unsigned char speed_right)
{
  switch (direction)
  {
  case 0:
    digitalWrite(MOTOR_L_1, HIGH);
    digitalWrite(MOTOR_L_2, LOW);
    digitalWrite(MOTOR_R_1, HIGH);
    digitalWrite(MOTOR_R_2, LOW);
    isForward = true;
    isStop = false;
    break;

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
  analogWrite(ENA_PIN, speed_left);
  analogWrite(ENB_PIN, speed_right);
}

void CAR_stop()
{
  digitalWrite(MOTOR_L_1, LOW);
  digitalWrite(MOTOR_L_2, LOW);
  digitalWrite(MOTOR_R_1, LOW);
  digitalWrite(MOTOR_R_2, LOW);
  isStop = true;
}

void forward()
{
    CAR_move(FORWARD, SPEED, SPEED);
    delay(MOVETIME);
    CAR_stop();
    delay(MOVETIME);
}

void back()
{
    CAR_move(BACK, SPEED, SPEED);
    delay(MOVETIME);
    CAR_stop();
    delay(MOVETIME);
}

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);

  pinMode(LEFT_TRIG, OUTPUT);
  pinMode(LEFT_ECHO, INPUT);
  pinMode(RIGHT_TRIG, OUTPUT);
  pinMode(RIGHT_ECHO, INPUT);

  pinMode(LEFT_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);

  pinMode(ENA_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);
  pinMode(MOTOR_L_1, OUTPUT);
  pinMode(MOTOR_L_2, OUTPUT);
  pinMode(MOTOR_R_1, OUTPUT);
  pinMode(MOTOR_R_2, OUTPUT);

  myservo.attach(2);
  myservo.write(ANGLE_MIDDLE);
}

void loop() 
{
  if (flag == 0) {
    //rearParking();
    control();
  }
  else if (flag == 1) {
    rearParking1();
  }
  else if (flag == 2) {
    rearParking2();
  }
}

void control()
{
  getstr = Serial.read();

  if (getstr == 'a') {
    CAR_move(FORWARD, SPEED, SPEED);
  }
  else if (getstr == 'b') {
    CAR_move(BACK, SPEED, SPEED);
  }
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
  else if (getstr == 'i') {
    angle = ANGLE_MIDDLE;
    myservo.write(angle);
  }
  else if (getstr == 'j') {
    angle = ANGLE_LEFT1;
    myservo.write(angle);
  }
  else if (getstr == 'k') {
    angle = ANGLE_LEFT2;
    myservo.write(angle);
  }
  else if (getstr == 'l') {
    angle = ANGLE_LEFT3;
    myservo.write(angle);
  }
  else if (getstr == 'm') {
    angle = ANGLE_RIGHT1;
    myservo.write(angle);
  }
  else if (getstr == 'n') {
    angle = ANGLE_RIGHT2;
    myservo.write(angle);
  }
  else if (getstr == 'o') {
    angle = ANGLE_RIGHT3;
    myservo.write(angle);
  }
  else if (getstr == 'p') {
    SPEED = 180;
    rearParking();
  }
  else if (getstr == 'r') {
    SPEED = 180;
    parallelParking();
  }
}

void parallelParking()
{
  setMiddle();

  int gap = 0;
  int distance;

  for (int count = PARALLELAREA; count >= 0; count--)
  {
    forward();

    distance = getRight();

    if (distance > 800)
    {
      gap++;
    }
    else
    {
      gap = 0;
    }

    if (gap > PARALLELGAP)
    {
      parallel();
      //flag = 3;
      break;
    }
  }
}

void rearParking()
{
  int gap = 0;
  int distance;
  
  setMiddle();

  for (int count = REARAREA; count >= 0; count--)
  {
    forward();

    int right = getRight();

    if (right > 800 && right != 0)
    {
      gap++;
    }
    else
    {
      gap = 0;
    }

    if (gap > REARGAP)
    {
      break;
    }
  }
  if (gap <= REARGAP)
  {
    return;
  }

  for(int i=0; i<5; i++)
  {
    forward();
  }
  flag=1;
}

void rearParking1()
{
  int left = getLeft();
  
  if (left < 1200 && left !=0)
  {
    flag=2;
    return;
  }
  
  setRight();
  back();
}

void rearParking2()
{
  if (isHorizontal())
  {
    setMiddle();
    flag=0;
    return;
  }

  int left = getLeft();
  int right = getRight();

  angle = ANGLE_MIDDLE + (right - left) / 30;
  if (angle > ANGLE_RIGHT3)
    angle = ANGLE_RIGHT3;
  else if (angle < ANGLE_LEFT3)
    angle = ANGLE_LEFT3;

  if (angle != ANGLE_MIDDLE)
  {
    myservo.write(ANGLE_MIDDLE);
    delay(MOVETIME);

    forward();

    myservo.write(angle);
    delay(MOVETIME);
    
    back();

    if (isHorizontal())
    {
      setMiddle();
      flag=0;
      return;
    }
  }

  myservo.write(angle);
  delay(MOVETIME);
  back();
}

void parallel()
{
  for(int i=0; i<1; i++)
  {
    forward();
  }

  setRight();

  for(int i=0; i<15; i++)
  {
    back();
  } 

  delay(MOVETIME*2);
  setLeft();

  for(int i=0; i<5; i++)
  {
    back();
  }

  delay(MOVETIME*2);
  setRight();

  for(int i=0; i<3; i++)
  {
    forward();
  }

  delay(MOVETIME*2);
  setLeft();

  for(int i=0; i<3; i++)
  {
    back();
  }

  delay(MOVETIME*2);
  setRight();

  for(int i=0; i<6; i++)
  {
    forward();
  }

  delay(MOVETIME*2);
  setMiddle();

  for(int i=0; i<1; i++)
  {
    back();
  }
}

