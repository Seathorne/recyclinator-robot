
/*   FUNCTIONS
     1.  void MtrSpeed()      -  line  9
     2.  void GetEncoders()   -  line 23
     3.  void EncRst()        -  line 57
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

//----------------------------------------
//-----------------------------------------
void Encoders()  {
  Serial2.write(SynchByte);                    //Get Encoder - right then left
  Serial2.write(0x25);
  delay(50);
  
  if (Serial2.available() > 0) {  
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

//------------------------------------------
void EncRst() {
  Serial2.write(SynchByte);                  //Reset Encoders
  Serial2.write(0x35);
  delay(50);
} 
