
/*   FUNCTIONS
     1. void SetPinModes()             -  line 10
     2.  void InitializeSerialPorts()  -  line 19
     3.  void ConfigMotors()           -  line 27
*/

//-----------------------------------------

void SetPinModes () {
  pinMode(rc_active, INPUT);            // zero in Auto mode
  pinMode(LtF_TrigEchoPin, OUTPUT);
  pinMode(RtF_TrigEchoPin, OUTPUT);
  pinMode(LtR_TrigEchoPin, OUTPUT);
  pinMode(RtR_TrigEchoPin, OUTPUT);
  pinMode(LtHall_pin, OUTPUT);
  pinMode(RtHall_pin, OUTPUT);
}

//--------------------------------------------
void InitializeSerialPorts(){
  Serial.begin(9600);                    //Monitor
  Serial1.begin(57600);                  //Logomatic communications
  Serial2.begin(9600);                   //MD49 Motor Controller
  Serial3.begin(19200);                  //Uno comm - requests/resets Gyro angle
}

//-------------------------------------------
void ConfigMotors(){
  //  Begin by Setting & Stopping Motors
  Serial2.write(SynchByte);                  //Set Motor Controller Mode to independent motor control
  Serial2.write(SetMode);
  Serial2.write(0x00);
  delay(20);
  Serial2.write(SynchByte);                  //Disable Timeout - Turn motor controller on, then reset Arduino
  Serial2.write(0x38);
  delay(20);
  Serial2.write(SynchByte);                  //Turn Off(0x36);  On (0x37) Speed Control (encoder feedback)
  Serial2.write(0x36);
  delay(20);
//  Begin by Stopping Motors   
  Serial2.write(SynchByte);                  //Left Motor Stop
  Serial2.write(0x31);
  Serial2.write(128);
  Serial2.write(SynchByte);                  //Right Motor Stop
  Serial2.write(0x32);
  Serial2.write(128);
  
  Serial2.write(SynchByte);                  //Set Acceleration time constant
  Serial2.write(0x33);
  Serial2.write(0);
  
  Serial2.write(SynchByte);                  //Reset Encoders
  Serial2.write(0x35);  
}

//---------------------------------------
 
