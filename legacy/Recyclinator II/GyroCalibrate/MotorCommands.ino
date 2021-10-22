
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
void MtrSpeed(byte LtSpeed, byte RtSpeed) {

      Serial2.write(SynchByte);      //Left Motor      
      Serial2.write(0x31);
      Serial2.write(LtSpeed); 
      delay(20);     
      Serial2.write(SynchByte);      //Right Motor
      Serial2.write(0x32);
      Serial2.write(RtSpeed);
      delay(20);
}

//-------------------------------------------
void Encoders(long &encoderLt, long &encoderRt)  {
  Serial2.write(SynchByte);                    //Get Encoder - right then left
  Serial2.write(0x25);

  delay(50);
  if (Serial2.available() > 7) {  
  encoderLt = long(Serial2.read())<<24;        //Get Left Encoder
  encoderLt += long(Serial2.read())<<16;
  encoderLt += long(Serial2.read())<<8;
  encoderLt += long(Serial2.read());  

  encoderRt = long(Serial2.read())<<24;      //Get Right Encoder Counts
  encoderRt += long(Serial2.read())<<16;
  encoderRt += long(Serial2.read())<<8;
  encoderRt += long(Serial2.read());
  }
}

//--------------------------------------------
void SetAcceleration(byte accel) {
    Serial2.write(SynchByte);                  //Set Acceleration time constant
    Serial2.write(0x33);
    Serial2.write(accel);
    delay(20);   
}

//------------------------------------------
void EncRst() {
  Serial2.write(SynchByte);                  //Reset Encoders
  Serial2.write(0x35);
  delay(100);
} 
