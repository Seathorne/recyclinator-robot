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

void Robot::step(bool Flip)
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
      _stepWallFollowComp(Flip);
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

bool Robot::checkWall(SonarLoc LeftS, SonarLoc RightS)
{
  const float exDistance=201;
  float currRangeL = this->sonar(LeftS).Range();
  float currRangeR = this->sonar(RightS).Range();
  float currRange=currRangeL+currRangeR;
  Serial.println(String(currRange));
  float  normRange=abs(currRange-exDistance);
  Serial.println(String(normRange));
  if(normRange<5) return true;
  else return false;
}

void Robot::startWallFollowComp(float range, double distance, double distanceL, double speed, SonarLoc sonarR, SonarLoc sonarL)
{
  _rangeSetpoint = range;
  _rangeSetpointL = distanceL;
  _distanceSetpoint = distance;
  _driveSpeed = speed;
  _wallFollowSonar = sonarR;
  _wallFollowSonarL = sonarL;
  
  _mode = Mode::WallFollowing;
  this->_stepWallFollowComp(false);
}

Feature Robot::detectFeatureRepeatedComp(SonarLoc sonarLoc, float &range) {   //this hasn't changed aside from losing a var.
  constexpr float FeatureThreshold = 15;
  constexpr float JunctionThreshold = 200;  

  constexpr int BufferSize = 2 * 2;       
  constexpr int RepeatSize = 2;           
  
  static float ranges[SonarLoc::Count][BufferSize];
  static bool firstTime[SonarLoc::Count] = { true, true, true, true, true, true, true };
  

  
  /* Read current range */
  float currRange = this->sonar(sonarLoc).Range();
  Serial.println(String(currRange));
  /* First time only: initialize buffer */
  if (firstTime[sonarLoc]) {                                    //failure vector 1; firstTime fails to change
    firstTime[sonarLoc] = false;
    for (int i = 0; i < BufferSize; i++) {
      ranges[sonarLoc][i] = currRange;
    }
    range = -1;
    Serial.println("Performing first time setup. If this happens more than once, this is bugged.");
    return Feature::None;
  }

  /* Shift in new reading */
  for (int i = 0; i < BufferSize-1; i++) {
    ranges[sonarLoc][i] = ranges[sonarLoc][i+1];
  }
  ranges[sonarLoc][BufferSize-1] = currRange;

  /* Detect whether feature present in repeated readings */
  bool repeated = true;
  float depths[RepeatSize];
  float old = ranges[sonarLoc][BufferSize-1 - RepeatSize];
  for (int i = 0; i < RepeatSize; i++) {
    depths[i] = ranges[sonarLoc][BufferSize-1 - i] - old;
    if (depths[i] < FeatureThreshold) {
      repeated = false;
      break;
    }
  }

  /* Take average depth of feature */
  float depth = 0;
  for (int i = 0; i < RepeatSize; i++) {
    depth += depths[i];
  }
  depth = abs(depth/RepeatSize);
  // ranges[sonarLoc][0]-range
  
  /* Characterize feature */
  Serial.println("Feature| depth = " + String(depth));
  Feature detected = (depth >= JunctionThreshold && repeated)
    ? Feature::Junction
    : (depth >= FeatureThreshold && repeated)
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
    default:
      Serial.println("Feature| None");                                                                                                  //modified condition for error testing.
      break;
  }

  range = currRange; 
  return detected;
}
float Robot::getRangeSetpoint()
{
  return _rangeSetpoint;
}
float Robot::getRangeSetpointL()
{
  return _rangeSetpointL;
}

void Robot::_stepWallFollowComp(bool Flip)
{
  const float Kp = 0.005;   
  const float Kd = .7;
  const float speedMaxDiff = 10 / 128.0;
  float range;
  float error;
  static float prevError = 0;

  if (_mode != Mode::WallFollowing)
  {
    Serial.println("Warning! Robot::_stepWallFollow(...) : _mode is " + String(_mode) + "; should be Mode::WallFollowing.");
    return;
  }
  if(Flip=false)    //if flip = false
  {
    range = _sonars[_wallFollowSonar].Range();   //set range to right sonar range
    error = _rangeSetpoint - range;              //calc error from that
  }
  else
  {
    range = _sonars[_wallFollowSonarL].Range();  //set range to left sonar range
    error = _rangeSetpointL - range;             //calc error from that
  }
  float delError = (error - prevError);
  prevError = error;

  float corr = -(Kp*error + Kd*delError);             //wall follow as usual (Should? work with this method.)
  Serial.println("Following| corr=" + String(corr));
  if (corr > 1)
    corr = 1;
  else if (corr < -1)
    corr = -1;
  
  float corrLim = corr*speedMaxDiff;                    //should have some wonk stuff with the compensation for 1 iteration
  float leftSpeed = _driveSpeed + corrLim;              //but it shouldn't matter.
  float rightSpeed = _driveSpeed;
  _drive.SetSpeed(leftSpeed, rightSpeed);
}