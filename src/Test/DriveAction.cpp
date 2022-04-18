#include "DriveAction.h"

DriveAction::DriveAction(Robot *robot, double distance, double speed)
    : Action(robot) {
  _distanceSetpoint = distance;
  _speedSetpoint = speed;
}

void DriveAction::start() {
  Serial.println("DriveAction| starting");
  _robot->startDrive(_distanceSetpoint, _speedSetpoint);
};

void DriveAction::step() {
  Serial.println("DriveAction| stepping");
  _robot->step();
};

bool DriveAction::shouldEnd() const {
  return (_robot->mode() != Mode::Driving);
}

void DriveAction::end() {
  Serial.println("DriveAction| ending");
  _robot->stop();
}
