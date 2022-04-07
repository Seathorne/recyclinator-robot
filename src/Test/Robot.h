#ifndef ROBOT_H
#define ROBOT_H

#include "Drive.h"
#include "Gyro.h"
#include "Sonar.h"

enum Mode
{
  Stopped,
  Rotating,
  Driving,
  WallFollowing,
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

class Robot
{
public:
    static constexpr int GyroPin = 55;
    static constexpr int SonarPins[SonarLoc::Count] = { 24, 25, 26, 27, 28, 29, 34 };

    Robot();
    void init();
    void update();
    void step();

    void startRotate(float angleDeg);
    void stepRotate();

    void startDrive(double distance, double speed);
    void stepDrive();

    void startWallFollow(float range, double distance, double speed, SonarLoc sonar);

    void stop();

    Mode mode() const;

    Drive drive() const;
    Gyro gyro() const;
    Sonar sonar(SonarLoc location) const;
    
private:
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

    void _setMode(Mode mode);
    
    void _driveForward(float speed, float angle);
    void _stepWallFollow();
};

#endif // ROBOT_H
