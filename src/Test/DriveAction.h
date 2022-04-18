#ifndef DRIVE_ACTION_H
#define DRIVE_ACTION_H

#include "Action.h"

class DriveAction : public Action
{
public:
  DriveAction(Robot *robot, double distance, double speed);
  bool shouldEnd() const override;

private:
  double _distanceSetpoint;
  double _speedSetpoint;

  void start() override;
  void step() override;
  void end() override;
};

#endif // DRIVE_ACTION_H
