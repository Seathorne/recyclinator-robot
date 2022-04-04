#include "Robot.h"

Robot::Robot(Drive &drive, Gyro &gyro)
{
    this->drive = drive;
    this->gyro = gyro;
}