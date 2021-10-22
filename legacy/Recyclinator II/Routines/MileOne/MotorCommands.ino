
/*   FUNCTIONS
     1.  void MtrSpeed()      -  line  9
     2.  void GetEncoders()   -  line 23
     3.  void serialEvent2()  -  line 34
     4.  void EncRst()        -  line 57
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
void GetEncoders() {
  ReceiveEnc = true;
  Serial2.write(SynchByte);
  Serial2.write(0x25);
  delay(50);
  EncIndex = 0;
}

//-------------------------------------------
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
//-------------------------------------------
//----------------------------------------
void serialEvent2() {
  byte Enc[8];
  
  while (Serial2.available()) {
    Enc[EncIndex] = Serial2.read();
    EncIndex++;
    if(EncIndex == 8) {
      encoderRt = long(Enc[0])<<24;        //Get Right Encoder
      encoderRt += long(Enc[1])<<16;
      encoderRt += long(Enc[2])<<8;
      encoderRt += long(Enc[3]);  
    
      encoderLt = long(Enc[4])<<24;      //Get Left Encoder Counts
      encoderLt += long(Enc[5])<<16;
      encoderLt += long(Enc[6])<<8;
      encoderLt += long(Enc[7]);
      ReceiveEnc = false;
    }
  }
}

//--------------------------------------------
//------------------------------------------
void EncRst() {
  Serial2.write(SynchByte);                  //Reset Encoders
  Serial2.write(0x35);
  delay(50);
} 
