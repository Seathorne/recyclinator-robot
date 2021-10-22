void Compute()  {
 float temp1;
 float temp2;

//   angles alpha and beta (deg) measured CW from left perpendicular to heading
//   theta (rad) measured positive CW from heading
  temp1 = D1*sin(alpha/radToDeg) - D2*sin(beta/radToDeg);
  temp2 = D2*cos(beta/radToDeg) - D1*cos(alpha/radToDeg);
  theta = atan2(temp1, temp2);

  y = D1*(sin(alpha/radToDeg)*cos(theta) + cos(alpha/radToDeg)*sin(theta));
}

//_______________________________________________________________
void Pairs() {

  for (int i = 1; i < num; i++)  {
    for (int j = (i+1); j < (num+1); j++ ) {
      D1 = DOne[i];
      alpha = angAlpha[i];
      D2 = DTwo[j];
      beta = angBeta[j];
      Serial.print(i);
      Serial.write(9);
      Serial.print(j);
      Serial.write(9);
      Compute();
      Serial.print(y);
      Serial.write(9);
      Serial.println(theta*radToDeg);
    }
  }
}

