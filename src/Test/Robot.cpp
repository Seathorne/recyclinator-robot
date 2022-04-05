#include "Robot.h"

Robot::Robot(Drive &drive, Gyro &gyro)
  : _drive(drive),
    _gyro(gyro)
{ }

void Robot::startRotate(float angleDeg)
{
    float currAngle = _gyro.angleDeg();
    _angleSetpoint = currAngle + angleDeg;
    _isRotating = true;
    this->stepRotate();
}

bool Robot::isRotating() const
{
    return _isRotating;
}

void Robot::stepRotate()
{
  const float Kp = 1;
  const float Kd = 0.01;
  
  static double delError = 0;
  static double error = 0;
  double angle = _gyro.angleDeg();
  
  float newError = _angleSetpoint - angle;
  delError = newError - error;
  error = newError;
  
  float corr = Kp*error + Kd*delError;
  Serial.println("Rotate| orig corr = " + String(corr));

  // Normalize corrective factor
  corr /= 360.0;

  // Clamp between -1..1
  if (corr > 1) {
    corr = 1;
  } else if (corr < -1) {
    corr = -1;
  }
  
  Serial.println("Rotate| corr = " + String(corr));
  _drive.SetSpeed(corr, -corr);
}

//driveforward functions start

void Robot::startDrive(double distance, double speed)
{
    double distanceSoFar;
    _drive.getDistance(distanceSoFar, NULL); //use right wheel as reference since left is the correcting wheel, and will have variable distance traveled.
    _distanceSetPoint=distance+distanceSoFar;
    _driveSpeed=speed;    //set this as a non-1 value, please and thank you.
    _angleSetPoint= _gyro.angleDeg;
    this->stepDrive();
}

bool Robot::isDriving() const
{
  return _isDriving;
}

void Robot::stepDrive()
{
    double distanceSoFar;
    _drive.getDistance(distanceSoFar, NULL);
    if(distanceSoFar<_distanceSetPoint){
     this->forwardMovement(_driveSpeed, _angleSetPoint, _gyro);
     _isDriving=true;
    }
    else
    {
      _drive.setSpeed(0,0);
      _isDriving=false;
    }
}
//the forwardmovement function stuck into robot.
void Robot::forwardmovement(float speed, float angle, Gyro &gyro);
{
  float Speed=speed;
  float dist=55;
  float currentAng=gyro.angleDeg();
  const float Kp = 0.25;
  const float Kd = 0.01;  
  float correctedAngle;
  correctedAngle=currentAng-angle;
  
  if(correctedAngle>180)
  {
    correctedAngle-=360;
  }
  else if(correctedAngle<-180)
  {
    correctedAngle+=360;
  }
  
  static float error = 0;
  static float delError = 0;
  
  float newError = 0-correctedAngle;
  delError=newError-error;
  error=newError;
  Serial.println("Set Angle "+String(angle));
  Serial.println("Current Angle "+String(gyro.angleDeg()));
  float corr = -(Kp*error+Kd*delError);
  Serial.println("Corr value"+String(corr));
  if (corr > .1) {
    corr = .1;
  }
    else if (corr < -.1)
  {
    corr = -.1;
    }


  //on top of that, I guess you have to really ask how we're going to merge the two, as two routines
  //controlling the motor independently is bound to cause some issue.
  float leftSpeed = speed;
  float rightSpeed= speed+corr;
  Serial.println("s");
  Serial.println(leftSpeed);
  drive.SetSpeed(leftSpeed, rightSpeed);
}

//driveforward functions end