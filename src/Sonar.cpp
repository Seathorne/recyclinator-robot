#include "Sonar.h"

Sonar::Sonar(int pin)
: _pin { pin } { }

void Sonar::Update() {
  this->GetRange();
}

float Sonar::Range() const {
  return _range;
}

void Sonar::GetRange() {
  // Ping duration, in milliseconds
  const int PING_DURATION = 12;
  
  // Conversion factor, ??? to meters
  const float TO_METERS = 17.241380;

  // Ping sonar
  pinMode(_pin, OUTPUT);
  
  digitalWrite(_pin, HIGH);
  delayMicroseconds(PING_DURATION);
  digitalWrite(_pin, LOW);
  
  pinMode(_pin, INPUT);

  // Receive echo; convert to range
  float echo = pulseIn(_pin, HIGH);
  _range = echo * TO_METERS;
}
