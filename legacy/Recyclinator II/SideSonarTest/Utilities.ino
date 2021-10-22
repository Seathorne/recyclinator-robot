void InitialiseSerialPorts(){
  Serial.begin(9600);                    //Monitor
  Serial1.begin(57600);                  //Logomatic communications
  Serial2.begin(9600);                   //MD49 Motor Controller
}

void SetPinModes(){
  pinMode(rc_active, INPUT);            // zero in Auto mode
/*  
  pinMode(LtF_TrigEchopin, OUTPUT);
  pinMode(RtF_TrigEchopin, OUTPUT);
  pinMode(LtR_TrigEchopin, OUTPUT);
  pinMode(RtR_TrigEchopin, OUTPUT);
*/
}

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
}

void MtrSpeed(byte &LtSpeed, byte &RtSpeed) {
      Serial2.write(SynchByte);      //Speed 1 - Left Motor      
      Serial2.write(0x31);
      Serial2.write(LtSpeed); 
      delay(20);     
      Serial2.write(SynchByte);      //Speed 2 - Right Motor
      Serial2.write(0x32);
      Serial2.write(RtSpeed);
      delay(20);
}
