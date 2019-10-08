/*
  This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
  It won't work with v1.x motor shields! Only for the v2's with built in PWM
  control

  For use with the Adafruit Motor Shield v2
  ---->	http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);


int leftSensorPin = A0; //Sensor pin
int rightSensorPin = A1;

void setup() {
  long baudRate = 9600;
  Serial.begin(baudRate);           // set up Serial library at 9600 bps

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  //   Set the speed to start, from 0 (off) to 255 (max speed)
//
//  leftMotor->run(FORWARD);
//  rightMotor->run(FORWARD);
//  // turn on motor
  rightMotor->run(RELEASE);
  leftMotor->run(RELEASE);

}

void loop() {

  int rightSensor = analogRead(rightSensorPin);
  int leftSensor = analogRead(leftSensorPin);

//    Serial.print("Right: ");Serial.print(rightSensor); //normal at ground should be around 300
//    Serial.println();
//    Serial.print("Left: ");Serial.print(leftSensor); //normal at ground should be around 300
//    Serial.println();


  if (leftSensor > 850) { //Forward for left motor = backwards in real life
    leftMotor->setSpeed(25);
    rightMotor -> setSpeed(0);
    leftMotor->run(BACKWARD);
    rightMotor ->run(BACKWARD);
  }

  else if (rightSensor > 850) {
    rightMotor->setSpeed(25);
    leftMotor -> setSpeed(0);
    rightMotor->run(FORWARD);
    leftMotor->run(FORWARD);
  }

  else {
    leftMotor -> setSpeed(15);
    rightMotor -> setSpeed(15);
    rightMotor->run(FORWARD);
    leftMotor->run(BACKWARD); //forward for this motor (mounted backwards)
  }
}
