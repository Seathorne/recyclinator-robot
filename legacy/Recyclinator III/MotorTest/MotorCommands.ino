
/*   FUNCTIONS
     1.  void MtrSpeed()        -  line 11
     2.  void GetEncoders()     -  line 23
     3.  void serialEvent2()    -  line 33
     4.  void SetAcceleration() -  line 57
     4.  void EncRst()          -  line 65
*/
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
//-----------------------------------------

void Encoders(long &encoderLt, long &encoderRt)  {
  Serial2.write(SynchByte);                    //Get Encoder - right then left
  Serial2.write(0x25);

  delay(50);
  if (Serial2.available() > 7) {  
  encoderRt = long(Serial2.read())<<24;        //Get Right Encoder
  encoderRt += long(Serial2.read())<<16;
  encoderRt += long(Serial2.read())<<8;
  encoderRt += long(Serial2.read());  

  encoderLt = long(Serial2.read())<<24;      //Get Left Encoder Counts
  encoderLt += long(Serial2.read())<<16;
  encoderLt += long(Serial2.read())<<8;
  encoderLt += long(Serial2.read());
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
  delay(50);
} 
