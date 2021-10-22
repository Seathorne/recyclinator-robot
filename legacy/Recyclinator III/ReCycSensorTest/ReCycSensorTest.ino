   

/*********************************************************
                           ARDUINO MEGA
                        RECYLINATOR III
                      Initial Sensor Tests
                          EMG40 & MD49
                      7 September 2021
                        
RC Test   9/4
Side Sonar Test  9/13
Reduce Global Variables 9/15 - incomplete
Begin Hall  Follow Testing - 9/16
Hall following not working - Jan 2018

**********************************************************/


#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);

#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41); //board I2C address

#include <LIDARLite.h>
LIDARLite myLidarLite;

#define SERVOMIN   90 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  440 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

String cmd   = "";                   // the Command 
float arg[3] = {0};                  // you can pass up one argument in a serial command
int ArgIndex;                        // index into arguments
String inputString = "";             // a string to hold incoming serial data

byte go;
byte sonarFlag = false;
byte lidarFlag = false;
byte IMUFlag = true;

int servonum = 0;
int pulselen;

//   Program Pings an Ultrasonic Sensor and returns a distance in cm
//  Arduino pin assignments
int LeftHallSonar_pin   = 24;  //sonar #5
int RightHallSonar_pin  = 25;  //sonar #6
int LeftRearSonar_pin   = 26;  //sonar #2
int LeftFrontSonar_pin  = 27;  //sonar #1
int RightFrontSonar_pin = 28;  //sonar #4
int RightRearSonar_pin  = 29;  //sonar #3

float LeftHallRange;
float RightHallRange;
float LeftRearRange;
float LeftFrontRange;
float RightFrontRange;
float RightRearRange;

float servoAng;
float servoAngle;

void setup() {

  Serial.begin(9600);
  pinMode(LeftHallSonar_pin, OUTPUT);
  pinMode(RightHallSonar_pin, OUTPUT);
  pinMode(LeftRearSonar_pin, OUTPUT);
  pinMode(LeftFrontSonar_pin, OUTPUT);
  pinMode(RightFrontSonar_pin, OUTPUT);
  pinMode(RightRearSonar_pin, OUTPUT); 

// Initialize the IMU
if(!bno.begin())  {
      //There was a problem detecting the BNO055 .. check connections
      Serial.print("Ooops, no BNO055 detected ..  Check wiring or I2C address");
      while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);
  delay(500);  

  myLidarLite.begin(0, true);
  myLidarLite.configure(0);

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}

void loop() {
  if(sonarFlag == true) {  
    LeftHallRange = SonarRange(LeftHallSonar_pin);
    Serial.print(LeftHallRange,0); 
    delay(20);
  
    RightHallRange = SonarRange(RightHallSonar_pin);
    Serial.write(9);
    Serial.print(RightHallRange,0); 
    delay(20);  
  
    LeftRearRange = SonarRange(LeftRearSonar_pin);
    Serial.write(9);
    Serial.print(LeftRearRange,0); 
    delay(20);  
  
    LeftFrontRange = SonarRange(LeftFrontSonar_pin);
    Serial.write(9);
    Serial.print(LeftFrontRange,0); 
    delay(20);  
  
    RightFrontRange = SonarRange(RightFrontSonar_pin);
    Serial.write(9);
    Serial.print(RightFrontRange,0); 
    delay(20);  
  
    RightRearRange = SonarRange(RightRearSonar_pin);
    Serial.write(9);
    Serial.println(RightRearRange,0); 
    delay(20);  
    Serial.println(" ");
  }

  if(lidarFlag == true) {
    LidarPoint();
  }

  if(IMUFlag == true) {
    IMU();
  }
}
