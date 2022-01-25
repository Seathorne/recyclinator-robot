#include "Drive.h"

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
  this->SendCommand(SET_SPEED_LEFT, (byte)(value * 0xFF));
}

void Drive::SetSpeedRight(float value) {
  this->SendCommand(SET_SPEED_RIGHT, (byte)(value * 0xFF));
}

void Drive::SetAccel(float value) {
  this->SendCommand(SET_ACCEL, (byte)(value * 0xFF));
}

void Drive::GetEncoderCounts() {
  this->SendCommand(DriveCommand::GET_ENCODERS);
  
  delay(50); // TODO: refactor to remove delay
  
  _encoder_right = (long)_serial.read() << 24;
  _encoder_right += (long)_serial.read() << 16;
  _encoder_right += (long)_serial.read() << 8;
  _encoder_right += (long)_serial.read();

  _encoder_left = (long)_serial.read() << 24;
  _encoder_left += (long)_serial.read() << 16;
  _encoder_left += (long)_serial.read() << 8;
  _encoder_left += (long)_serial.read();
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
