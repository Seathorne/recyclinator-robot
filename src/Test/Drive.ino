#include "Drive.h"
#include <math.h>

Drive::Drive(HardwareSerial& serial)
: _serial{ serial }
{ }

void Drive::Init() {
  Serial.println("Drive| initializing");
  _serial.begin(Drive::BAUD_RATE);
  this->ResetEncoderCounts();
}

void Drive::Update() {
  static long int prevTime;

  long int currTime = millis();

  double left, right;
  double prevDistance = GetDistance(left, right);
  GetEncoderCounts();
  double currDistance = GetDistance(left, right);
  
  _speed += (currDistance - prevDistance) / (currTime - prevTime) / 1000.0;

  prevTime = currTime;
}

void Drive::ResetEncoderCounts() const {
  this->SendCommand(RESET_ENCODERS);
}

void Drive::SetSpeed(float left, float right) {
  this->SetSpeedLeft(left);
  this->SetSpeedRight(right);
}

void Drive::SetSpeedLeft(float value) {
  // Transform [-1..1] --> [0..255]
  if (value > 1) value = 1;
  else if (value < -1) value = -1;
  this->SendCommand(SET_SPEED_LEFT, (byte)((value + 1.0) * 127.5));
}

void Drive::SetSpeedRight(float value) {
  // Transform [-1..1] --> [0..255]
  if (value > 1) value = 1;
  else if (value < -1) value = -1;
  this->SendCommand(SET_SPEED_RIGHT, (byte)((value + 1.0) * 127.5));
}

void Drive::SetAccel(float value) {
  // Transform [0..1] --> [0..255]
  if (value > 1) value = 1;
  else if (value < 0) value = 0;
  this->SendCommand(SET_ACCEL, (byte)(value * 255));
}

void Drive::GetEncoderCounts() {
  this->SendCommand(DriveCommand::GET_ENCODERS);
  
  delay(50); // TODO: refactor to remove delay

  Serial.println("Drive| reading encoders");
  
  _encoder_left = (long)_serial.read() << 24;
  _encoder_left += (long)_serial.read() << 16;
  _encoder_left += (long)_serial.read() << 8;
  _encoder_left += (long)_serial.read();

  _encoder_right = (long)_serial.read() << 24;
  _encoder_right += (long)_serial.read() << 16;
  _encoder_right += (long)_serial.read() << 8;
  _encoder_right += (long)_serial.read();

  _distance_left = (2*M_PI*WHEEL_RADIUS*(double)_encoder_left)/(double)REVOLUTIONS;
  _distance_right = (2*M_PI*WHEEL_RADIUS*(double)_encoder_right)/(double)REVOLUTIONS;
}

void Drive::SendCommand(DriveCommand command) const {
  _serial.write((byte)DriveCommand::SYNC);
  _serial.write((byte)command);
}

void Drive::SendCommand(DriveCommand command, byte value) const {
  _serial.write((byte)DriveCommand::SYNC);
  _serial.write((byte)command);
  _serial.write(value);
}

void Drive::GetEncodersLong(long &left, long &right) {
  left = _encoder_left;
  right = _encoder_right;
}

double Drive::GetDistance(double &left, double &right) const {
  left = _distance_left;
  right = _distance_right;
  return (_distance_left + _distance_right) * 0.5;
}

double Drive::DistanceLeft() const {
  return _distance_left;
}

double Drive::DistanceRight() const {
  return _distance_right;
}

double Drive::GetSpeed() const {
  return _speed;
}
