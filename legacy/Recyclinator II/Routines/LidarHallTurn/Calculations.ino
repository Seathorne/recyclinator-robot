void Compute()  {
 float temp1;
 float temp2;

  temp1 = D1*cos(alpha) - D2*cos(beta);
  temp2 = D2*sin(beta) - D1*sin(alpha);
  theta = atan2(temp1, temp2);

  y1 = D1*cos(alpha - theta);
  y2 = D2*cos(beta - theta);
  Serial.print(theta*radToDeg);
  Serial.write(9);
  Serial.print(y1);
  Serial.write(9);
  Serial.println(y2);
}

