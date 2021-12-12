
/*   FUNCTIONS
     1.  void MtrSpeed()       -  line 11
     2.  void GetEncoders()    -  line 24
     3.  void EncRst()         -  line 52
     4.  void SetAcceleraton() -  line 59
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
//-------------------------------------------

void Encoders()  {
byte Enc[8];  

  EncIndex = 0;   
  ReceiveEnc = true;
  Serial2.write(SynchByte);                    //Get Encoder - right then left
  Serial2.write(0x25);
  delay(50);

  while (Serial2.available()) {
    Enc[EncIndex] = Serial2.read();
    EncIndex++;
    if(EncIndex == 8) {
      encoderLt = long(Enc[0])<<24;        //Get Right Encoder
      encoderLt += long(Enc[1])<<16;
      encoderLt += long(Enc[2])<<8;
      encoderLt += long(Enc[3]);  
    
      encoderRt = long(Enc[4])<<24;      //Get Left Encoder Counts
      encoderRt += long(Enc[5])<<16;
      encoderRt += long(Enc[6])<<8;
      encoderRt += long(Enc[7]);
      ReceiveEnc = false;
    }
  }  
}
//-------------------------------------------

void EncRst() {
  Serial2.write(SynchByte);                  //Reset Encoders
  Serial2.write(0x35);
  delay(50);
} 
//-------------------------------------------

void SetAcceleration(byte accel) {
    Serial2.write(SynchByte);                  //Set Acceleration time constant
    Serial2.write(0x33);
    Serial2.write(accel);
    delay(20);   
}
