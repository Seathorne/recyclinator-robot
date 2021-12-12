void Report() {
  Serial1.print(millis());
  Serial1.write(9);
  Serial1.print(rangeRight);
  Serial1.write(9);
  Serial1.print(error);
  Serial1.write(9);
  Serial1.print(delError);
  Serial1.write(9);
  Serial1.print(leftSpeed); 
  Serial1.write(9);
  Serial1.println(rightSpeed);   
}
