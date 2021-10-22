
/*   FUNCTIONS
     1.  void MtrSpeed()      -  line  9
     2.  void GetEncoders()   -  line 23
     3.  void serialEvent2()  -  line 34
     4.  void EncRst()        -  line 57
*/
//---------------------------------------
void MtrSpeed(byte LtSpeed, byte RtSpeed) {

      Serial2.write(SynchByte);      //Right Motor      
      Serial2.write(0x31);
      Serial2.write(RtSpeed); 
      delay(20);     
      Serial2.write(SynchByte);      //Left Motor
      Serial2.write(0x32);
      Serial2.write(LtSpeed);
      delay(20);
}

//----------------------------------------
//-----------------------------------------
void GetEncoders() {
  Serial2.write(SynchByte);
  Serial2.write(0x25);
  delay(50);
}

//------------------------------------------
void EncRst() {
  Serial2.write(SynchByte);                  //Reset Encoders
  Serial2.write(0x35);
  delay(50);
} 
