#ifndef DRIVE
#define DRIVE

enum DriveCommand {
  SYNC = 0x00,
  GET_ENCODERS = 0x25,
  SET_SPEED_LEFT = 0x31,
  SET_SPEED_RIGHT = 0x32,
  SET_ACCEL = 0x33,
  RESET_ENCODERS = 0x35
};

class Drive {
  const int BAUD_RATE = 9600;
  
  public:
    Drive(HardwareSerial& serial);

    void Update();

    void ResetEncoderCounts() const;
    
    void SetSpeed(float left, float right);
    void SetSpeedLeft(float value);
    void SetSpeedRight(float value);

    void SetAccel(float value);
  
  private:
    HardwareSerial& _serial;
    
    long _encoder_left;
    long _encoder_right;

    void GetEncoderCounts();

    void SendCommand(DriveCommand command, byte value) const;
    void SendCommand(DriveCommand command) const;
};

#endif DRIVE
