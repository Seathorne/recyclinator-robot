#ifndef ROBOT_H
#define ROBOT_H

#include "Drive.h"
#include "Gyro.h"

class Robot
{
public:
    Robot(Drive &drive, Gyro &gyro);

    void startRotate(float angleDeg);
    bool isRotating();
    void stepRotate();

    void startDrive(double distance, double speed);
    bool isDriving();
    void stepDrive();

private:
    Drive *drive;
    Gyro *gyro;

    double _angleSetpoint;
    double _distanceSetpoint;
    double _driveSpeed;
};

#endif // ROBOT_H