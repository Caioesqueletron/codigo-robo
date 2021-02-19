//ARDUINO OBSTACLE AVOIDING CAR Video - https://youtu.be/h-B42_HXL00//
// Before uploading the code you have to install the necessary library//
//AFMotor Library https://learn.adafruit.com/adafruit-motor-shield/library-install //
//NewPing Library https://github.com/eliteio/Arduino_New_Ping.git // 
//Servo Library https://github.com/arduino-libraries/Servo.git //

#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A3 
#define ECHO_PIN A4
#define MAX_DISTANCE 100 
#define MAX_SPEED 500 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 200
#define TRIG_PIN2 A1
#define ECHO_PIN2 A2


NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing sonar2(TRIG_PIN2, ECHO_PIN2, MAX_DISTANCE);

AF_DCMotor motor1(1, MOTOR12_64KHZ);
// Atras lado direito
AF_DCMotor motor2(2, MOTOR12_64KHZ);
//Frente lado direito
AF_DCMotor motor3(3, MOTOR34_64KHZ);
//Frente lado esquerdo
AF_DCMotor motor4(4, MOTOR34_64KHZ);
//Lado esquerdo atras
Servo myservo;   
Servo myservo2;

boolean goesForward=false;
int distance = 100;
int distance2 = 100;
int speedSet = 0;
int max_speed = 400;
void setup() {

  myservo.attach(10);  
  myservo2.attach(9);
  myservo.write(115); 
  myservo2.write(115);
  delay(2000);
  distance = readPing();
  delay(70);
  distance2 = readPing2();
 
}

void loop() {
 int distanceR = 0;
 int distanceL = 0;
 delay(40);

 Serial.begin(9600);
 if(distance<=25 || distance2 <=25)
 {
  moveStop();
  delay(100);
  moveBackward();
  delay(100);
  moveStop();
  delay(100);
  distanceR = lookRight();
  delay(100);
  distanceL = lookLeft();
  delay(100);

  if(distanceR>=distanceL)
  { 
    
    turnRight();
    moveStop();
  } 
  
  else
  
  {
    turnLeft();
    moveStop();
  }
 } 
 
 else
 {
  moveForward();
 }
 distance = readPing();
 delay(70);
 distance2 = readPing2();
 Serial.print(distance);
 Serial.print(distance2);
}

int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

int lookLeft()
{
    myservo2.write(170); 
    delay(500);
    int distance = readPing2();
    delay(100);
    myservo2.write(115); 
    return distance;
    
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}
int readPing2() { 
  delay(70);
  int cm = sonar2.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD);     
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
   }
  }
}

void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor3.run(BACKWARD);
    motor2.run(BACKWARD);
    motor4.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}  

void turnRight() {
    //motor1.setSpeed(max_speed);
    //motor3.setSpeed(max_speed);
    //motor2.setSpeed(max_speed);
    //motor4.setSpeed(max_speed);
    //delay(5);
  motor1.run(FORWARD);
  motor3.run(FORWARD);
  motor2.run(BACKWARD);
  motor4.run(BACKWARD);     
  delay(500);
  motor1.run(FORWARD);      
  motor3.run(FORWARD);
  motor2.run(FORWARD);
  motor4.run(FORWARD);      
} 
 
void turnLeft() {
     //motor1.setSpeed(max_speed);
    //motor3.setSpeed(max_speed);
    //motor2.setSpeed(max_speed);
    //motor4.setSpeed(max_seed);
    //delay(5);
  motor1.run(BACKWARD);     
  motor3.run(BACKWARD);  
  motor2.run(FORWARD);
  motor4.run(FORWARD);   
  delay(5);
  motor1.run(FORWARD);     
  motor3.run(FORWARD);
  motor2.run(FORWARD);
  motor4.run(FORWARD);
}
