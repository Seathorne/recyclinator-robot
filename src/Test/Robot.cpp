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

void Robot::startDrive(double distance, double speed)
{
  
}

bool Robot::isDriving() const
{
  return _isDriving;
}

void Robot::stepDrive()
{
  
}
