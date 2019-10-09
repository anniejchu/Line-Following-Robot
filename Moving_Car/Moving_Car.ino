#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

//left motor = M1 | right motor = M2
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);


int leftSensorPin = A0; //left IR sensor
int rightSensorPin = A1; //right IR sensor
int RightSpeed;
int LeftSpeed;

void setup() {
  long baudRate = 9600;
  Serial.begin(baudRate); //setting up serial communication

  AFMS.begin();  // create with the default frequency 1.6KHz


  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);

  rightMotor->run(RELEASE);
  leftMotor->run(RELEASE);

}

void loop() {

  int rightSensor = analogRead(rightSensorPin);
  int leftSensor = analogRead(leftSensorPin);

  Serial.print("Right: "); Serial.print(rightSensor); //normal at ground should be around 300
  Serial.println();
  Serial.print("Left: "); Serial.print(leftSensor); //normal at ground should be around 300
  Serial.println();
  Serial.print("Rs: "); Serial.print(RightSpeed);
  Serial.println();
  Serial.print("Ls: "); Serial.print(LeftSpeed);

  if (leftSensor > 850) { //Forward for left motor = backwards in real life
    RightSpeed = 0;
    LeftSpeed = 50;
    leftMotor->setSpeed(50);
    rightMotor -> setSpeed(0);
    leftMotor->run(BACKWARD);//left motor forwards
    rightMotor ->run(BACKWARD);//right motor backwards
  }

  else if (rightSensor > 850) {
    RightSpeed = 50;
    LeftSpeed = 0;
    rightMotor->setSpeed(50);
    leftMotor -> setSpeed(0);
    rightMotor->run(FORWARD); //right motor forwards
    leftMotor->run(FORWARD); //left motor backwards
  }

  else {
    RightSpeed = 30;
    LeftSpeed = 30;
    leftMotor -> setSpeed(30);
    rightMotor -> setSpeed(30);
    rightMotor->run(FORWARD); //right motor forwards
    leftMotor->run(BACKWARD); //left motor forwards
  }
}
