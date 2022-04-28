#ifndef Lidar_H
#define Lidar_H

  #include "Arduino.h"
//////////////////carryover////////////////////
#include <Wire.h>
#include "Adafruit_PWMServoDriver.h"
#include "LIDARLite.h"
//////////////////////////////////////////////

//lidar class////////////////////////////////
class Lidar: public LIDARLite{
public:
  Lidar();
  void Start();
  void Start(int pwmcode, int UpSwitch, int DownSwitch, int UpDirect, int DownDirect, int LiftMotor, int Encoder);
  void Update();
  void UpdateEncoder();
  void MoveTo(int pos);
  void MoveBy(int num);
  void RotateTo(int pos);
  void RotateBy(int num);
  int _range;
  int Encode;
  void HandleCalibration();
  int MaxCount;
private:
  	//motor ints
  int servonum=0;
  float Angle;
  int pulselen;
  int TopSwitch;
  int BottomSwitch;
  int Dir1;
  int Dir2;			
  int LiftMotor;
  int Direction;
  int EncoderTimeout = 200;
  int volatile Counter = 0;
  int Calibrated;
  bool Moving;
  int TargetCount;
  
  Adafruit_PWMServoDriver pwm;
  void ReadLimits();

  void LiftMotorOff();
  void ResetEncoderTimeout();
  int Point(float ang);
};
////////////////////////////////////////////
#endif
