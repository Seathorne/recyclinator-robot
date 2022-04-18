#ifndef ACTION_H
#define ACTION_H

#include "Robot.h"

enum Step
{
  Unstarted,
  Running,
  Done,
};

class Action
{
public:
  Action(Robot *robot);
  void run();
  bool isDone() const;

protected:
  Robot *_robot;

  virtual void start() = 0;
  virtual void step() = 0;
  virtual bool shouldEnd() const = 0;
  virtual void end() = 0;

private:
  Step _step;

  void setStep(Step step);
};

#endif // ACTION_H
