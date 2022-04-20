#include "Action.h"

Action::Action(Robot *robot) {
  _robot = robot;
  setStep(Unstarted);
}

void Action::run() {
  switch (_step) {
    case Unstarted:
      Serial.println("Action| starting");
      this->start();
      setStep(Running);
      break;
    case Running:
      Serial.println("Action| running");
      if (this->shouldEnd()) {
        Serial.println("Action| ending");
        setStep(Done);
        this->end();
      } else {
        Serial.println("Action| continuing");
        this->step();
      }
      break;
    default:
      Serial.println("Action| run() called when _step == " + String(_step));
      break;
  }
  Serial.println("Action| step = " + String(_step));
}

void Action::setStep(Step step) {
  Serial.println("Action| _step changed from " + String(_step) + " to " + String(step));
  _step = step;
}

bool Action::isDone() const {
  return (_step == Done);
}
