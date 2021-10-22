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
  
  N = 0;
  
  for (int i = 1; i < num; i++)  {
    for (int j = (i+1); j < (num+1); j++ ) {
      N++;
      D1 = DOne[i];
      alpha = angAlpha[i];
      D2 = DTwo[j];
      beta = angBeta[j];
      Serial.print(i);
      Serial.write(9);
      Serial.print(j);
      Serial.write(9);

      Serial1.print(i);
      Serial1.write(9);
      Serial1.print(j);
      Serial1.write(9);      
      Compute();
      Y[N] = y;
      Theta[N] = theta;
      Serial.print(y,0);
      Serial.write(9);
      Serial.println(theta*radToDeg,1);

      Serial1.print(y,0);
      Serial1.write(9);
      Serial1.println(theta*radToDeg,1);      
    }
  }
}

//-------------------------------------------------------------
void AvgStdDev()  {
float sumY;
float sumTheta;
float sumYSqr;
float sumThetaSqr;

  Serial.print("N = ");
  Serial.println(N);

  Serial1.print("N = ");
  Serial1.println(N);  
  sumY = 0;  
  sumTheta = 0;
  sumYSqr = 0;
  sumThetaSqr = 0;
  
  for (int i = 1; i < (N+1); i++) {
    sumY += Y[i];
    sumYSqr += Y[i]*Y[i];
    sumTheta += Theta[i];
    sumThetaSqr += Theta[i]*Theta[i];
  }
  avgY = sumY/N;
  avgTheta = sumTheta/N;

  YStdev = sqrt(N*sumYSqr - sumY*sumY)/N;

  ThetaStdev = sqrt(N*sumThetaSqr - sumTheta*sumTheta)/N; 

  Serial.print(" avg & std dev   ");
  Serial.print(avgY,0);
  Serial.write(9);
  Serial.print(YStdev,1);
  Serial.write(9);
  Serial.print(avgTheta*radToDeg,1);
  Serial.write(9);
  Serial.println(ThetaStdev*radToDeg,1);

  Serial1.print(" avg & std dev   ");
  Serial1.print(avgY,0);
  Serial1.write(9);
  Serial1.print(YStdev,1);
  Serial1.write(9);
  Serial1.print(avgTheta*radToDeg,1);
  Serial1.write(9);
  Serial1.println(ThetaStdev*radToDeg,1);  
}

//--------------------------------------------------
void Filter() {

float sumY;
float sumTheta;
float numII;
int II[15];

  sumY = 0;
  sumTheta = 0;
  numII = 0;
  
  for (int i = 1; i < (N+1); i++)  {
    if (abs(avgY - Y[i]) < YStdev) {
      Serial.print(i);
      Serial.write(9);
      
      Serial1.print(i);
      Serial1.write(9);      
      sumY += Y[i];
      II[i] = i;
      numII += 1;
    }
  }
  Serial.write(9);
  Serial.print(numII,0);
  Serial.println("   ");

  Serial1.write(9);
  Serial1.print(numII,0);
  Serial1.println("   ");
  YBar = sumY/numII;

  for (int i = 1; i < (numII+1); i++) {
    sumTheta += Theta[II[i]];
  }
    Serial.println(sumTheta);  
  ThetaBar = sumTheta/numII;

  Serial.print(" filter: YBar, ThetaBar  ");
  Serial.write(9);
  Serial.print(YBar,0);
  Serial.write(9);
  Serial.println(ThetaBar*radToDeg,1);

  Serial1.print(" filter: YBar, ThetaBar  ");
  Serial1.write(9);
  Serial1.print(YBar,0);
  Serial1.write(9);
  Serial1.println(ThetaBar*radToDeg,1);  
}

