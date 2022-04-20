#include "Gyro.h"

Gyro::Gyro(int pin)
  : _pin(pin)
{ }

void Gyro::init() {
  /* Initialize IMU device */
  Serial.println("Gyro| initializing");
  sensor = Adafruit_BNO055(_pin);
  if (!sensor.begin()) {
    Serial.println("Warning: no BNO055 IMU detected.");
  } else Serial.println("Success: BNO055 IMU detected.");
  delay(1000);
  sensor.setExtCrystalUse(true);
  delay(500);
}

void Gyro::update() {
  static long int prevTime;

  long int currTime = millis();
  double prevAngle = _angleDeg;
  
  sensor.getEvent(&sensorEvent);
  _angleDeg = sensorEvent.orientation.x;
  if (_angleDeg > 180.0) {
    _angleDeg -= 360.0;
  }

  _angularVel = (_angleDeg - prevAngle) / (currTime - prevTime) / 1000.0;
  prevTime = currTime;
}

float Gyro::angleDeg() const {
  return _angleDeg;
}

float Gyro::angleRad() const {
  constexpr const float DegToRad = PI/180.0;
  return _angleDeg * DegToRad;
}

float Gyro::angularVel() const {
  return _angularVel;
}
