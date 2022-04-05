#ifndef ROBOT_H
#define ROBOT_H

#include "Drive.h"
#include "Gyro.h"

class Robot
{
public:
    Robot(Drive &drive, Gyro &gyro);

    void startRotate(float angleDeg);
    bool isRotating() const;
    void stepRotate();

    void startDrive(double distance, double speed);
    bool isDriving() const;
    void stepDrive();
    void forwardmovement(float speed, float angle, Gyro &gyro); //to be set to private once test file no longer requires it.
private:
    Drive _drive;
    Gyro _gyro;

    double _angleSetpoint;
    bool   _isRotating;
    
    double _distanceSetpoint;
    double _driveSpeed;
    bool   _isDriving;
};

#endif // ROBOT_H
