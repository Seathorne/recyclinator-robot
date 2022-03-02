#include "Gyro.h"

Gyro::Gyro(int pin)
  : _pin(pin)
{ }

void Gyro::init() {
  /* Initialize IMU device */
  sensor = Adafruit_BNO055(_pin);
  if (!sensor.begin()) {
    Serial.println("Warning: no BNO055 IMU detected.");
  } else Serial.println("Success: BNO055 IMU detected.");
  delay(1000);
  sensor.setExtCrystalUse(true);
  delay(500);
}

void Gyro::update() {
  sensor.getEvent(&sensorEvent);
  _angleDeg = sensorEvent.orientation.x;
  if (_angleDeg > 180.0) {
    _angleDeg -= 360.0;
  }
}

float Gyro::angleDeg() const {
  return _angleDeg;
}
