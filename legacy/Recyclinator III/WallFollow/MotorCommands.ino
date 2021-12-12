
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

void EncRst() {
  Serial2.write(SynchByte);          //Reset Encoders
  Serial2.write(0x35);
  delay(50);
} 
//-------------------------------------------

void SetAcceleration(byte accel) {
    Serial2.write(SynchByte);        //Set Acceleration time constant
    Serial2.write(0x33);
    Serial2.write(accel);
    delay(20);   
}
