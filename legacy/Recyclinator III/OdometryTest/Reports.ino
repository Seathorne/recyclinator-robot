
void Print() {
  Serial1.print(millis());
  Serial1.write(9);
  Serial1.print(encoderLt);
  Serial1.write(9);
  Serial1.print(encoderRt);
  Serial1.write(9);  
  Serial1.print(x);
  Serial1.write(9);
  Serial1.print(y);
  Serial1.write(9);
  Serial1.print(U);
  Serial1.write(9);
  Serial1.print(theta/DegTRad);
  Serial1.write(9);
  Serial1.print(leftDelta);
  Serial1.write(9);
  Serial1.print(rightDelta);
  Serial1.write(9);
  Serial1.println(LtSpd);   
  Serial1.println("  ");
  Serial1.println("-----------------");
  Serial1.println("  "); 
}
