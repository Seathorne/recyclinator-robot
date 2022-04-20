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
    
    Robot();
    void init();
    void update();
    void step(bool Flip);

    void startRotate(float angleDeg);
    void stepRotate();

    void startDrive(double distance, double speed);
    void stepDrive();

    void startWallFollow(float range, double distance, double speed, SonarLoc sonar);
    void setRangeSetpoint(float range);
    void setRangeSetpointL(float range);
    float getRangeSetpoint();
    float getRangeSetpointL();
    void stop();

    Feature detectFeatureRepeated(SonarLoc sonar, float &range);

    Mode mode() const;

    Drive drive() const;
    Gyro gyro() const;
    Sonar sonar(SonarLoc location) const;
  
    bool checkWall(SonarLoc leftS, SonarLoc RightS);
  
    void startWallFollowComp(float range, double distance, double distanceL, double speed, SonarLoc sonarR, SonarLoc sonarL);
    void stepWallFollowComp(bool Flip);
      
    Feature detectFeatureRepeatedComp(SonarLoc sonarLoc, float &range);
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
    float _rangeSetpointL;
    SonarLoc _wallFollowSonar;
    SonarLoc _wallFollowSonarL;

    void _setMode(Mode mode);
    
    void _driveForward(float speed, float angle);
    void _stepWallFollow();
};

#endif // ROBOT_H
