#ifndef ROBOT_H
#define ROBOT_H

#include "Drive.h"
#include "Gyro.h"

enum Mode
{
  Stopped,
  Rotating,
  Driving,
  WallFollowing,
};

class Robot
{
public:
    Robot(Drive &drive, Gyro &gyro);
    void init();
    void update();
    void step();

    void startRotate(float angleDeg);
    void stepRotate();

    void startDrive(double distance, double speed);
    void stepDrive();
    void forwardmovement(float speed, float angle, Gyro &gyro); //to be set to private once test file no longer requires it.

    void stop();

    Mode mode() const;

    Drive drive() const;
    Gyro gyro() const;
    
private:
    Drive _drive;
    Gyro _gyro;

    Mode _mode;

    double _angleSetpoint;
    bool   _isRotating;
    
    double _distanceSetpoint;
    double _driveSpeed;
    bool   _isDriving;

    void _setMode(Mode mode);
};

#endif // ROBOT_H
