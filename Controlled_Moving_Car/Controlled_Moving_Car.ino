#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

//left motor = M1 | right motor = M2
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

int leftSensorPin = A0; //left IR sensor
int rightSensorPin = A1; //right IR sensor
int receivedChar; //initiating variable to hold character input
boolean isRunning = false; //boolean for continuous driving
boolean spd = false;;

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
  recvOneChar();  
  if (isRunning && spd){
    runCar(50); //will run car if isRunning boolean is true
  }
  else if (isRunning && spd == false) {
    runCar(30);
  }
  else if (isRunning == false){
    stopCar(); //will stop car if isRunning boolean is false
  }
}

void recvOneChar() {
  if (Serial.available() > 0) //detecting for serial input
  {
    receivedChar = Serial.read();
    if (receivedChar == 'f') { //will set isRunning true if g key is entered in serial monitor
      isRunning = true;
      spd = true;
    }
    else if (receivedChar == 'l') {
      isRunning = true;
      spd = false;
    }
    else if (receivedChar == 's') { //will set isRunning false if s key is entered in serial monitor
      isRunning = false;
    }
  }
}


void runCar(int spd) {
  int rightSensor = analogRead(rightSensorPin);
  int leftSensor = analogRead(leftSensorPin);
  
  if (leftSensor > 850) { //Forward for left motor = backwards in real life
    leftMotor->setSpeed(spd+20);
    rightMotor -> setSpeed(0);
    leftMotor->run(BACKWARD);//left motor forwards
    rightMotor ->run(BACKWARD);//right motor backwards
  }

  else if (rightSensor > 850) {
    rightMotor->setSpeed(spd+20);
    leftMotor -> setSpeed(0);
    rightMotor->run(FORWARD); //right motor forwards
    leftMotor->run(FORWARD); //left motor backwards
  }

  else {
    leftMotor -> setSpeed(spd);
    rightMotor -> setSpeed(spd);
    rightMotor->run(FORWARD); //right motor forwards
    leftMotor->run(BACKWARD); //left motor forwards
  }
}

void stopCar() {
  rightMotor->setSpeed(0);
  leftMotor->setSpeed(0);    
  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);
}
