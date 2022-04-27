#ifndef ROBOT_H
#define ROBOT_H

#include "Drive.h"
#include "Gyro.h"
#include "Hall.h"
#include "Sonar.h"

enum Mode
{
  Stopped,
  Rotating,
  Driving,
  WallFollowing,
  Roaming,
};

enum SonarLoc
{
  HallLeft,
  HallRight,
  BackLeft,
  FrontLeft,
  FrontRight,
  BackRight,
  Front,
  Count
};

enum Feature {
  None,
  Junction,
  Other,
};

class Robot
{
public:
    static constexpr int GyroPin = 55;
    static constexpr int SonarPins[SonarLoc::Count] = { 24, 25, 26, 27, 28, 29, 34 };
    static constexpr double Width = 33;
    
    Robot();
    void init();
    void update();
    void step();
    void stop();

    void resetOdometry();

    void setHall(const Hall *hall, Direction dir);
    void startRoam(const Hall *hall, Direction dir, double x, double y, double speed);
    void _stepRoam();

    void startRotate(float angleDeg);
    void stepRotate();

    void startDrive(double distance, double speed);
    void stepDrive();

    void startWallFollow(float range, double distance, double speed, SonarLoc sonar);
    void setRangeSetpoint(float range);
    float getRangeSetpoint();

    Feature detectFeatureBuffered(SonarLoc sonar, float &range);
    Feature detectFeatureRepeated(SonarLoc sonar, float &range);

    Mode mode() const;

    Drive drive() const;
    Gyro gyro() const;
    Sonar sonar(SonarLoc location) const;
  
    bool checkWall(SonarLoc leftS, SonarLoc RightS);
  
    void startWallFollowComp(float range, double distance, double speed, SonarLoc sonarR, SonarLoc sonarL);
      
    Feature detectFeatureRepeatedComp(SonarLoc sonarLoc, SonarLoc sonarLoc2, float &range);

    double getTime() const;

    double getDistance() const;
    double getVelocity() const;
    double getAcceleration() const;

    double getAngle() const;
    double getAngularVelocity() const;
    double getAngularAcceleration() const;

    double getX() const;
    double getY() const;

private:
    /* Odometry variables */
    double _t, _dt;
    double _x, _y;
    double _dist, _vel, _accel;
    double _theta, _vTheta, _aTheta;

    static bool rangeMatches(double actual, double expected);
    void _updateOdometry();
    void _syncOdometry();

    /* Hall variables */
    const Hall* _initHall;
    const Hall* _hall;
    Direction _initDirection;
    Direction _direction;

    Drive _drive;
    Gyro _gyro;
    Sonar _sonars[SonarLoc::Count] = {
      Sonar(SonarPins[SonarLoc::HallLeft]),
      Sonar(SonarPins[SonarLoc::HallRight]),
      Sonar(SonarPins[SonarLoc::BackLeft]),
      Sonar(SonarPins[SonarLoc::FrontLeft]),
      Sonar(SonarPins[SonarLoc::FrontRight]),
      Sonar(SonarPins[SonarLoc::BackRight]),
      Sonar(SonarPins[SonarLoc::Front]),
    };

    Mode _mode;
    
    double _driveSpeed;
    double _angleSetpoint;
    double _distanceSetpoint;
    float _rangeSetpoint;
    SonarLoc _wallFollowSonar;
    SonarLoc _wallFollowSonarL;

    void _setMode(Mode mode);
    
    void _driveForward(float speed, float angle);
    void _stepWallFollow();
};

#endif // ROBOT_H
