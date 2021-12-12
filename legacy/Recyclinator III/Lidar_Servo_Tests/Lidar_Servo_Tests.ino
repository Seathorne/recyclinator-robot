   

/*********************************************************
                           ARDUINO MEGA
                          RECYLINATOR III
                         Lidar & Servo Tests
                           17 November 2021                 
                        
  Program uses the Command module code to direct the servo position.
  Enter the word ang, space, and the angle to point the lidar.
  e.g.  (ang 90) will aim the servo straight ahead and then a lidar measurement maide.
  Angle varies from 0 (right), 90 (ahead), 180 (left).
  The SERVOMIN and SERVOMAX parameters, zeros and scales the servo positions - 
    **  Do Not Alter **

**********************************************************/

#include <LIDARLite.h>
LIDARLite myLidarLite;

#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41); //board I2C address

#define SERVOMIN  120 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  475 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

String cmd   = "";                   // the Command 
float arg[3] = {0};                  // you can pass up one argument in a serial command
int ArgIndex;                        // index into arguments
String inputString = "";             // a string to hold incoming serial data

byte go;

int servonum = 0;
int pulselen;

float servoAng;
float servoAngle;

void setup() {
  Serial.begin(9600);
  delay(500);  

  myLidarLite.begin(0, true);
  myLidarLite.configure(0);

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}

void loop() {

    LidarPoint();
}
