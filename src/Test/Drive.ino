#include "Drive.h"
#include <math.h>
Drive::Drive(HardwareSerial& serial)
: _serial{ serial } {
  _serial.begin(Drive::BAUD_RATE);
  this->ResetEncoderCounts();
}

void Drive::Update() {
  this->GetEncoderCounts();
  // TODO: calculate real pos/vel/accel
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
  this->SendCommand(SET_SPEED_LEFT, (byte)((value + 1.0) * 127.5));
}

void Drive::SetSpeedRight(float value) {
  // Transform [-1..1] --> [0..255]
  this->SendCommand(SET_SPEED_RIGHT, (byte)((value + 1.0) * 127.5));
}

void Drive::SetAccel(float value) {
  // Transform [0..1] --> [0..255]
  this->SendCommand(SET_ACCEL, (byte)(value * 255));
}

void Drive::GetEncoderCounts() {
  this->SendCommand(DriveCommand::GET_ENCODERS);
  
  delay(50); // TODO: refactor to remove delay
  
  _encoder_left = (long)_serial.read() << 24;
  _encoder_left += (long)_serial.read() << 16;
  _encoder_left += (long)_serial.read() << 8;
  _encoder_left += (long)_serial.read();

  _encoder_right = (long)_serial.read() << 24;
  _encoder_right += (long)_serial.read() << 16;
  _encoder_right += (long)_serial.read() << 8;
  _encoder_right += (long)_serial.read();

  _distance_left =(2*M_PI*WHEEL_RADIUS*(double)_encoder_left)/(double)REVOLUTIONS;
  _distance_right =(2*M_PI*WHEEL_RADIUS*(double)_encoder_right)/(double)REVOLUTIONS;
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
