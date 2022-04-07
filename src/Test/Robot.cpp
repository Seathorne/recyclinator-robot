#include "Robot.h"

Robot::Robot()
  : _drive(Serial2),
    _gyro(GyroPin)
{ }

void Robot::init()
{
  /* Initialize subsystems */
  _drive.Init();
  _gyro.init();
  
  for (int i = 0; i < SonarLoc::Count; i++)
  {
    _sonars[i].Init();
  }
}

void Robot::update()
{
  /* Update sensors & subsystems */
  _drive.Update();
  _gyro.update();

  for (int i = 0; i < SonarLoc::Count; i++)
  {
    _sonars[i].Update();
  }
}

void Robot::step()
{
  switch (_mode)
  {
    case Rotating:
      stepRotate();
      break;

    case Driving:
      stepDrive();
      break;

    case WallFollowing:
      _stepWallFollow();
      break;
    
    default: break;
  }
}

void Robot::startRotate(float angleDeg)
{
    float currAngle = _gyro.angleDeg();
    _angleSetpoint = currAngle + angleDeg;
    
    _mode = Mode::Rotating;
    this->stepRotate();
}

void Robot::stepRotate()
{
  const float Kp = 1;
  const float Kd = 0.01;
  const float AngleThreshold = 5;
  const float MinSpeed = 0.03;
  
  static double delError = 0;
  static double error = 0;

  if (_mode != Mode::Rotating)
  {
    Serial.println("Warning! Robot::stepRotate() : _mode is " + String(_mode) + "; should be Mode::Rotating.");
    return;
  }
  
  double angle = _gyro.angleDeg();
  
  float newError = _angleSetpoint - angle;
  delError = newError - error;
  error = newError;

  if (abs(error) <= AngleThreshold)
  {
    Serial.println("Rotate| Stopped rotating");
    stop();
    return;
  }
  
  float corr = Kp*error + Kd*delError;
  Serial.println("Rotate| orig corr = " + String(corr));

  // Normalize corrective factor
  corr /= 360.0;

  // Clamp between -1..1
  if (corr > 1) {
    corr = 1;
  } else if (corr < -1) {
    corr = -1;
  } else if (corr < MinSpeed && corr > 0) {
    corr = MinSpeed;
  } else if (corr > -MinSpeed && corr < 0) {
    corr = -MinSpeed;
  }
  
  Serial.println("Rotate| corr = " + String(corr));
  _drive.SetSpeed(corr, -corr);
}

//driveforward functions start

void Robot::startDrive(double distance, double speed)
{
  // Use right wheel as reference since left is the correcting wheel,
  //  and will have variable distance traveled.
  double distanceSoFar = _drive.DistanceRight();
  _distanceSetpoint = distance + distanceSoFar;
  _driveSpeed = speed;    //set this as a non-1 value, please and thank you.
  _angleSetpoint = _gyro.angleDeg();
  
  _mode = Mode::Driving;
  this->stepDrive();
}

void Robot::stepDrive()
{
  if (_mode != Mode::Driving)
  {
    Serial.println("Warning! Robot::stepDrive() : _mode is " + String(_mode) + "; should be Mode::Driving.");
    return;
  }
  
  double distanceSoFar = _drive.DistanceRight();
  if (distanceSoFar < _distanceSetpoint) {
    this->_driveForward(_driveSpeed, _angleSetpoint);
  } else {
    this->stop();
  }
}

void Robot::stop()
{
  _drive.SetSpeed(0,0);
  _setMode(Mode::Stopped);
}

void Robot::_driveForward(float speed, float angle)
{
  const float Kp = 0.01;
  const float Kd = 0.01;

  static float error = 0;
  static float delError = 0;
  
  if (_mode != Mode::Driving)
  {
    Serial.println("Warning! Robot::_driveForward(...) : _mode is " + String(_mode) + "; should be Mode::Driving.");
    return;
  }
  
  float Speed=speed;
  float dist=55;
  float currentAng = _gyro.angleDeg();
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
  
  float newError = 0-correctedAngle;
  delError=newError-error;
  error=newError;
  Serial.println("Set Angle "+String(angle));
  Serial.println("Current Angle " + String(_gyro.angleDeg()));
  float corr = -(Kp*error+Kd*delError);
  Serial.println("Corr value"+String(corr));
  if (corr > .1) {
    corr = .1;
  }
    else if (corr < -.1)
  {
    corr = -.1;
  }
    
  float leftSpeed = speed;
  float rightSpeed= speed+corr;
  _drive.SetSpeed(leftSpeed, rightSpeed);
}

//driveforward functions end

void Robot::startWallFollow(float range, double distance, double speed, SonarLoc sonar)
{
  _rangeSetpoint = range;
  _distanceSetpoint = distance;
  _driveSpeed = speed;
  _wallFollowSonar = sonar;

  _mode = Mode::WallFollowing;
  this->_stepWallFollow();
}

void Robot::_stepWallFollow()
{
  const float Kp = 0.2;
  const float Kd = 5;
  const float speedMaxDiff = 10 / 128.0;
  
  static float prevError = 0;

  if (_mode != Mode::WallFollowing)
  {
    Serial.println("Warning! Robot::_stepWallFollow(...) : _mode is " + String(_mode) + "; should be Mode::WallFollowing.");
    return;
  }

  float range = _sonars[_wallFollowSonar].Range();
  float error = _rangeSetpoint - range;
  float delError = (error - prevError);
  prevError = error;

  float corr = -(Kp*error + Kd*delError);
  Serial.println("Following| corr=" + String(corr));
  if (corr > 1)
    corr = 1;
  else if (corr < -1)
    corr = -1;
  
  float corrLim = corr*speedMaxDiff;
  float leftSpeed = _driveSpeed + corrLim;
  float rightSpeed = _driveSpeed;
  _drive.SetSpeed(leftSpeed, rightSpeed);
}

void Robot::setRangeSetpoint(float range) {
  _rangeSetpoint = range;
}

/* Provides simple feature detection based on 
 * a small buffer of past sonar readings and
 * recognition of quick increases in depth.
 * Returns the type of feature and its absolute
 * range from the robot.
 */
Feature Robot::detectFeature(SonarLoc sonarLoc, float &range) {
  constexpr float FeatureThreshold = 15;
  constexpr float JunctionThreshold = 100;

  constexpr int BufferSize = 6;
  
  static float ranges[BufferSize];
  static bool firstTime = true;

  /* Read current range */
  float currRange = this->sonar(sonarLoc).Range();

  /* First time only: initialize buffer */
  if (firstTime) {
    firstTime = false;
    for (int i = 0; i < BufferSize; i++) {
      ranges[i] = currRange;
    }
    range = -1;
    return Feature::None;
  }

  /* Shift in new reading */
  for (int i = 0; i < BufferSize-1; i++) {
    ranges[i] = ranges[i+1];
  }
  ranges[BufferSize-1] = currRange;

  /* Find mean of older readings */
  float oldRangeAvg = 0;
  int oldCount = (BufferSize + 1)/2;
  for (int i = 0; i < oldCount; i++) {
    oldRangeAvg += ranges[i];
  }
  oldRangeAvg /= oldCount;

  /* Find mean of newer readings */
  float newRangeAvg = 0;
  int newCount = BufferSize/2;
  for (int i = 0; i < newCount; i++) {
    newRangeAvg += ranges[i];
  }
  newRangeAvg /= newCount;

  /* Characterize feature */
  float depth = abs(newRangeAvg - oldRangeAvg); // abs -> detects pos & neg features
  Feature detected = (depth >= JunctionThreshold)
    ? Feature::Junction
    : (depth >= FeatureThreshold)
      ? Feature::Other
      : Feature::None;

  /* For debugging: print detected feature */
  switch (detected) {
    case Junction:
      Serial.println("Feature| detected end of hallway with depth " + String(depth) + " at range " + String(currRange) + " cm");
      break;
    case Other:
      Serial.println("Feature| detected feature with depth " + String(depth) + " at range " + String(currRange) + " cm");
      break;
  }

  range = currRange; // or newRangeAvg -- both have pros & cons
  return detected;
}

Drive Robot::drive() const
{
  return _drive;
}

Gyro Robot::gyro() const
{
  return _gyro;
}

Sonar Robot::sonar(SonarLoc location) const
{
  return _sonars[location];
}

Mode Robot::mode() const
{
  return _mode;
}

void Robot::_setMode(Mode mode)
{
  _mode = mode;
}
