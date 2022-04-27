#include "Robot.h"

#include "Halls.h" // for Halls::degreesBetween(Direction a, Direction b)

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

  SonarLoc left = SonarLoc::HallLeft;
  SonarLoc right = SonarLoc::HallRight;

  this->_updateOdometry();
}

void Robot::setHall(const Hall *hall, Direction dir) {
  _initHall = hall;
  _initDirection = dir;
}

void Robot::resetOdometry() {
  _dist = 0;
  _vel = 0;
  _accel = 0;
  _x = 0;
  _y = 0;
}

void Robot::_updateOdometry() {
  /* Update new odometry values */
  double t = millis() / 1000.0;
  double dt = t - _t;

  double dist = _drive.GetDistance();
  double vel = (dist - _dist) / dt;
  double accel = (vel - _vel) / dt;

  double theta = _gyro.angleRad();
  double vTheta = (theta - _theta) / dt;
  double aTheta = (vTheta - _vTheta) / dt;

  double dDist = (vel * dt) + (0.5 * accel * dt * dt);
  double x = _x + (dDist * sin(theta));
  double y = _y + (dDist * cos(theta));

  /* Update old values */
  _t = t;
  _dt = dt;
  _dist = dist;
  _vel = vel;
  _accel = accel;
  _theta = theta;
  _vTheta = vTheta;
  _aTheta = aTheta;
  _x = x;
  _y = y;
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

    case Roaming:
      _stepRoam();
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

void Robot::startRoam(const Hall *hall, Direction dir, double x, double y, double speed) {
  _hall = hall;
  _direction = dir;
  _x = x;
  _y = y;
  _driveSpeed = speed;
  _angleSetpoint = Halls::degreesBetween(_initDirection, dir);

  this->_stepRoam();
}

bool Robot::rangeMatches(double actual, double expected) {
  static constexpr double Threshold = 5;
  return (actual >= expected - Threshold) || (actual <= expected + Threshold);
}

void Robot::_syncOdometry() {
  constexpr const double HalfRobotWidth = 0.5 * Robot::Width;
  constexpr const SonarLoc LeftSonarLoc = SonarLoc::HallLeft;
  constexpr const SonarLoc RightSonarLoc = SonarLoc::HallRight;

  double rangeLeft = _sonars[LeftSonarLoc].Range();
  double rangeRight = _sonars[RightSonarLoc].Range();
  double measuredWidth = rangeLeft + rangeRight + Robot::Width;

  double expLeft, expRight, expWidth;
  bool isLeftConst = _hall->isWallConst(_y, Side::Left, expLeft);
  bool isRightConst = _hall->isWallConst(_y, Side::Right, expRight);
  bool isWidthConst = _hall->isWidthConst(_y, expWidth);
  double avgWidth = _hall->getWidth();

  if (rangeMatches(measuredWidth, avgWidth)
      || (isWidthConst && rangeMatches(measuredWidth, expWidth))) {
    _x = (rangeLeft + HalfRobotWidth) - expLeft;
  } else if (isLeftConst && rangeMatches(rangeLeft, expLeft)) {
    _x = (rangeLeft + HalfRobotWidth) - expLeft;
  } else if (isRightConst && rangeMatches(rangeRight, expRight)) {
    _x = expRight - (rangeRight + HalfRobotWidth);
  }

  // update _y
}

void Robot::_stepRoam() {
  static constexpr double ResponseTime = 5; // seconds
  static constexpr double MaxAngle = 20; // degrees
  
  if (_mode != Mode::Roaming) {
    Serial.println("Warning! Robot::_stepRoam(...) : _mode is " + String(_mode) + "; should be Mode::Roaming.");
    return;
  }

  this->_syncOdometry();

  if (_y > _hall->getLength()) {
    Serial.println("Roaming| reached end of hall, stopping... (hall length = " + String(_hall->getLength()) + "; y = " + String(_y) + ")");
    this->stop();
    return;
  }

  double xSetpoint = _hall->xSetpointAt(_y);
  double xError = xSetpoint - _x;
  double responseDistance = _vel * ResponseTime;
  
  double angleSetpoint = asin(xError/responseDistance);
  angleSetpoint = min(max(angleSetpoint, -MaxAngle), MaxAngle); // Clamp angleSetpoint) to [-MaxAngle..MaxAngle]
  
  this->_driveForward(_driveSpeed, angleSetpoint);
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
  const float Kp = 0.005;
  const float Kd = .7;
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
/*
Feature Robot::detectFeatureBuffered(SonarLoc sonarLoc, float &range) {   vestigial. does nothing that other replaced functions don't do.
  constexpr float FeatureThreshold = 15;
  constexpr float JunctionThreshold = 200;

  constexpr int BufferSize = 2 * 2;
  
  static float ranges[BufferSize];
  static bool firstTime = true;

  // Read current range 
  float currRange = this->sonar(sonarLoc).Range();

  // First time only: initialize buffer 
  if (firstTime) {
    firstTime = false;
    for (int i = 0; i < BufferSize; i++) {
      ranges[i] = currRange;
    }
    range = -1;
    return Feature::None;
  }

  // Shift in new reading 
  for (int i = 0; i < BufferSize-1; i++) {
    ranges[i] = ranges[i+1];
  }
  ranges[BufferSize-1] = currRange;
  
  // Find mean of older readings 
  float oldRangeAvg = 0;
  int oldCount = (BufferSize + 1)/2;
  for (int i = 0; i < oldCount; i++) {
    oldRangeAvg += ranges[i];
  }
  oldRangeAvg /= oldCount;

  // Find mean of newer readings 
  float newRangeAvg = 0;
  int newCount = BufferSize - oldCount;
  for (int i = oldCount; i < BufferSize; i++) {
    newRangeAvg += ranges[i];
  }
  newRangeAvg /= newCount;

  // Calculate depth of feature 
  float depth = abs(newRangeAvg - oldRangeAvg); // abs -> detects pos & neg features
//  Serial.println("Feature| newRangeAvg = " + String(newRangeAvg));
//  Serial.println("Feature| oldRangeAvg = " + String(oldRangeAvg));

  // Characterize feature //
  Serial.println("Feature| depth = " + String(depth));
  Feature detected = (depth >= JunctionThreshold)
    ? Feature::Junction
    : (depth >= FeatureThreshold)
      ? Feature::Other
      : Feature::None;

  // For debugging: print detected feature //
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
*/
Feature Robot::detectFeatureRepeated(SonarLoc sonarLoc, float &range) {     //slated for reevaluation once detectfeaturerepeatedcomp is functional
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
  if (firstTime[sonarLoc]) {
    firstTime[sonarLoc] = false;
    for (int i = 0; i < BufferSize; i++) {
      ranges[sonarLoc][i] = currRange;
    }
    range = -1;
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

void Robot::startWallFollowComp(float range, double distance, double speed, SonarLoc sonarR, SonarLoc sonarL)
{
  _rangeSetpoint = range;
  _distanceSetpoint = distance;
  _driveSpeed = speed;
  _wallFollowSonar = sonarR;
  _wallFollowSonarL = sonarL;
  
  _mode = Mode::WallFollowing;
  this->_stepWallFollow();
}

Feature Robot::detectFeatureRepeatedComp(SonarLoc sonarLoc, SonarLoc sonarLoc2, float &range) {
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

double Robot::getTime() const {
  return _t;
}

double Robot::getDistance() const {
  return _dist;
}

double Robot::getVelocity() const {
  return _vel;
}

double Robot::getAcceleration() const {
  return _accel;
}

double Robot::getAngle() const {
  return _theta;
}

double Robot::getAngularVelocity() const {
  return _vTheta;
}

double Robot::getAngularAcceleration() const {
  return _aTheta;
}

double Robot::getX() const {
  return _x;
}

double Robot::getY() const {
  return _y;
}
