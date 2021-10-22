void Compute()  {
 float temp1;
 float temp2;

//   angles alpha and beta (deg) measured CW from left perpendicular to heading
//  beta < alpha
//   theta measured positive CW from heading
  temp1 = D1*sin(alpha/radToDeg) - D2*sin(beta/radToDeg);
  temp2 = D2*cos(beta/radToDeg) - D1*cos(alpha/radToDeg);
  theta = atan2(temp1, temp2);

  y1 = D1*(sin(alpha/radToDeg)*cos(theta) + cos(alpha/radToDeg)*sin(theta));
  y2 = D2*(sin(beta/radToDeg)*cos(theta) + cos(beta/radToDeg)*sin(theta));;
  Serial.print(theta*radToDeg);
  Serial.write(9);
  Serial.print(y1);
  Serial.write(9);
  Serial.println(y2);
}

