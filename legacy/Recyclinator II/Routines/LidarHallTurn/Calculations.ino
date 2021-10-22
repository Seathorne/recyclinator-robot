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

//-----------------------------------------------------------
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
      Y[i] = y;
      Theta[i] = theta;
      Serial.print(y);
      Serial.write(9);
      Serial.println(theta*radToDeg);
    }
  }
}

//-------------------------------------------------------------
void AvgStdDev()  {
float sumY;
float sumTheta;
float sumYSqr;
float sumThetaSqr;

  sumY = 0;  
  sumTheta = 0;
  for (int i = 1; i < (num); i++) {
    sumY += Y[i];
    sumYSqr += Y[i]*Y[i];
    sumTheta += Theta[i];
    sumThetaSqr += Theta[i]*Theta[i];
  }

  avgY = sumY/(num-1);
  avgTheta = sumTheta/(num-1);

  YStdev = sq(num*sumYSqr - sumY*sumY)/num;
  ThetaStdev = sq(num*sumThetaSqr - sumTheta*sumTheta)/num; 

  Serial.print(" avg & std dev   ");
  Serial.print(avgY);
  Serial.write(9);
  Serial.print(YStdev);
  Serial.write(9);
  Serial.print(avgTheta);
  Serial.write(9);
  Serial.println(ThetaStdev);
}

//--------------------------------------------------
void Filter() {
float newAvg;
float sumY;
float sumTheta;
float numII;
int II[15];

  sumY = 0;
  numII = 0;
  
  for (int i = 1; i < num; i++)  {
    if (abs(avgY - Y[i]) < YStdev) {
      sumY += Y[i];
      II[i] = i;
      numII += 1;
    }
  }
  YBar = sumY/numII;

  for (int i = 1; i < numII+1; i++)
    sumTheta += Theta[II[i]];

  ThetaBar = sumTheta/numII;

  Serial.print(" filter: YBar, ThetaBar  ");
  Serial.print(YBar);
  Serial.write(9);
  Serial.println(ThetaBar);
}

