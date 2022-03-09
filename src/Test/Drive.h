#ifndef DRIVE
#define DRIVE
#define WHEEL_RADIUS 0.063
#define REVOLUTIONS 980
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

    void Init();
    void Update();

    void ResetEncoderCounts() const;
    
    void SetSpeed(float left, float right);
    void SetSpeedLeft(float value);
    void SetSpeedRight(float value);

    void SetAccel(float value);

    void GetEncodersLong(long &left, long &right);

    /* Returns the averaged left and right encoder distances, in meters */
    double GetDistance(double &encoder1, double &encoder2) const;
    
  private:
    HardwareSerial& _serial;
    
    long _encoder_left;
    long _encoder_right;
    double _distance_left;
    double _distance_right;

    void GetEncoderCounts();

    void SendCommand(DriveCommand command, byte value) const;
    void SendCommand(DriveCommand command) const;
};

#endif DRIVE
