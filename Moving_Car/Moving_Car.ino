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
Adafruit_DCMotor *rightMotor = AFMS.getMotor(1);
Adafruit_DCMotor *leftMotor = AFMS.getMotor(2);


int rightSensorPin = A0; //Sensor pin
int leftSensorPin = A1;

void setup() {
  long baudRate = 9600;
  Serial.begin(baudRate);           // set up Serial library at 9600 bps

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  //   Set the speed to start, from 0 (off) to 255 (max speed)
  rightMotor->setSpeed(150);
  leftMotor->setSpeed(150);
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
  // turn on motor
  rightMotor->run(RELEASE);
  leftMotor->run(RELEASE);

}

void loop() {
  uint8_t i;


  int rightSensor = analogRead(rightSensorPin);
  int leftSensor = analogRead(leftSensorPin);
  //  Serial.print("Right: ");Serial.print(rightSensor);
  //  Serial.println();
  //  Serial.print("Left: ");Serial.print(leftSensor);
  //  Serial.println();


  if (rightSensor < 1000) {
    rightMotor->setSpeed(100);
    rightMotor->run(FORWARD);}
    else {
      rightMotor -> setSpeed(0);
    }

  else if (leftSensor < 1000) {
  leftMotor->setSpeed(100);
  leftMotor->run(FORWARD);}
  else {
    leftMotor -> setSpeed(0);
  }
}














//  my2Motor->run(FORWARD);
//  for (i=0; i<255; i++) {
//    myMotor->setSpeed(i);
//    my2Motor->setSpeed(i);
//    delay(10);
//  }
//  for (i=255; i!=0; i--) {
//    myMotor->setSpeed(i);
//    my2Motor->setSpeed(i);
//    delay(10);
//  }
//
//  Serial.print("tock");
//
//  myMotor->run(BACKWARD);
//  my2Motor->run(BACKWARD);
//  for (i=0; i<255; i++) {
//    myMotor->setSpeed(i);
//    my2Motor->setSpeed(i);
//    delay(10);
//  }
//  for (i=255; i!=0; i--) {
//    myMotor->setSpeed(i);
//    my2Motor->setSpeed(i);
//    delay(10);
//  }
//
//  Serial.print("tech");
//  myMotor->run(RELEASE);
//  my2Motor->run(RELEASE);
//  delay(1000);
//}
