
void Print() {
  Serial1.print(millis() - T0);
  Serial1.write(9);
  Serial1.print(LtSpd);
  Serial1.write(9);
  Serial1.print(RtSpd);
  Serial1.write(9);
  Serial1.print(encoderLt);
  Serial1.write(9);
  Serial1.println(encoderRt); 
}
