#include <Servo.h> //standard library
#include <NewPing.h> //ultrasonic sensor function library.

//L298N control pins
const int LeftMotorForward=5;
const int LeftMotorBackward=4;
const int RightMotorForward=3;
const int RightMotorBackward=2;

//sensor pins
// me to #define den 8eteis mnhmh san to const int pixi.
#define trig_pin A1 // analog input 1
#define echo_pin A2 // analog input 2

//QUESTIONS

// 1) Giati vazei delays????

// gia na dwsei xrono sta shmata na kanoun kinhseis.

#define maximum_distance 200

boolean goesForward=false;
int distance=100;

//ousiastika kalei to sonar function
NewPing sonar(trig_pin, echo_pin,maximum_distance); //NewPing setup of pins and maximum distance.
Servo servo_motor; //the servo name


void setup() {
  // put your setup code here, to run once:

  pinMode(RightMotorForward ,OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  servo_motor.attach(11); // our servo pin

  servo_motor.write(90);
  delay(2000);
  distance=readPing();
  delay(100);
  distance=readPing();
  delay(100);
  distance=readPing();
  delay(100);
  distance=readPing();
  delay(100);

}

void loop() {
  // put your main code here, to run repeatedly:

  int distanceRight=0;
  int distanceLeft=0;
  delay(50);

  if (distance<=20)
  {
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight=lookRight();
    distanceLeft=lookLeft();
    delay(300);

    if (distance>=distanceLeft)
    {
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward();
  }
  distance=readPing();
}

int lookRight()
{
  // to write einai to stripsimo tou kefaliou se moires
  servo_motor.write(10);
  delay(500);

  // analoga to mege8os tou palmou pou lamvanei einai kai h apostash apo ta antikeimena
  int distance=readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft()
{
  servo_motor.write(170);
  delay(500);
  int distance=readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
  delay(100);
}

int readPing()
{
  delay(70);
  // edw diavazei to mege8os tou palmou
  int cm=sonar.ping_cm();
  // ama paei la8os h metrhsh kai gyrisei 0, tote ype8ese oti den hr8e pote kai kala einai makria.
  if (cm==0)
  {
    cm=250;
  }
  return cm;
}

void moveStop()
{
  // proypo8etei to Pinmode. To digitalWrite xeirizetai ta Volt sto ka8e pin. 5 Volt h 0 volt. Volt einai h piesh pou askeitai sta hlektrnia.
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward,LOW);
  digitalWrite(RightMotorBackward,LOW);
  digitalWrite(LeftMotorBackward,LOW);
}

void moveForward()
{
// mono an exei stamathsei na phgainei mprosta (goesForward=false), 8a synexisei na phgainei mprosta.
  if (!goesForward)
  {
    goesForward=true;

    digitalWrite(LeftMotorForward,HIGH);
    digitalWrite(RightMotorForward,HIGH);

    digitalWrite(LeftMotorBackward,LOW);
    digitalWrite(RightMotorBackward,LOW);
  }
}

void moveBackward()
{
  goesForward=false;

  digitalWrite(LeftMotorBackward,HIGH);
  digitalWrite(RightMotorBackward,HIGH);

  digitalWrite(LeftMotorForward,LOW);
  digitalWrite(RightMotorForward,LOW);
}

void turnRight()
{
  // otan strivei einai to delay pou xeirizetai to poses moires 8a stripsei o arduino
  digitalWrite(LeftMotorForward,HIGH);
  digitalWrite(RightMotorBackward,HIGH);

  digitalWrite(LeftMotorBackward,LOW);
  digitalWrite(RightMotorForward,LOW);

  delay(500);

  digitalWrite(LeftMotorForward,HIGH);
  digitalWrite(RightMotorForward,HIGH);

  digitalWrite(LeftMotorBackward,LOW);
  digitalWrite(RightMotorBackward,LOW);
}

void turnLeft()
{
  digitalWrite(LeftMotorBackward,HIGH);
  digitalWrite(RightMotorForward,HIGH);

  digitalWrite(LeftMotorForward,LOW);
  digitalWrite(RightMotorBackward,LOW);

  delay(500);

  digitalWrite(LeftMotorForward,HIGH);
  digitalWrite(RightMotorForward,HIGH);

  digitalWrite(LeftMotorBackward,LOW);
  digitalWrite(RightMotorBackward,LOW);
}
