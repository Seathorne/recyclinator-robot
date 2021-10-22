
void Print() {
  Serial1.print((millis() - timeTemp)/1000.0);
//  Serial1.write(9);
//  Serial1.print(LtMtrSpd);
//  Serial1.write(9);
//  Serial1.print(RtMtrSpd);
  Serial1.write(9);
  Serial1.print(encoderLt);
  Serial1.write(9);
  Serial1.println(encoderRt); 
}

//---------------------------------------------
//---------------------------------------------
void PrintMon() {
    Serial.print((millis() - timeTemp)/1000.0);
//  Serial.write(9);
//  Serial.print(LtMtrSpd);
//  Serial.write(9);
//  Serial.print(RtMtrSpd);
  Serial.write(9);
  Serial.print(encoderLt);
  Serial.write(9);
  Serial.println(encoderRt); 
}
