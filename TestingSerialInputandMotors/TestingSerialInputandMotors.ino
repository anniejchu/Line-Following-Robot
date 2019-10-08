#include <Wire.h>
#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
int receivedChar;
boolean isRunning = false;


void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  AFMS.begin();
  myMotor->setSpeed(150);
  myMotor->run(FORWARD);
  myMotor->run(RELEASE);
}

void loop() {

  recvOneChar();
  Serial.print("Nothing"); Serial.println();
  
  if (isRunning) {
    myMotor->setSpeed(30);
    myMotor->run(FORWARD);
  }
}

void recvOneChar() {

  if (Serial.available() > 0)
  {

    receivedChar = Serial.read();

    if (receivedChar == 'g') {
      runCar();
    }

    else if (receivedChar == 's') {
      stopCar();
    }
  }
}


void runCar() {
  Serial.print("running");
  myMotor->setSpeed(30);
  myMotor->run(FORWARD);
  isRunning = true;
}

void stopCar() {
  Serial.print("Stopped");
  myMotor ->setSpeed(0);
  myMotor->run(FORWARD);
  isRunning = false;
}
