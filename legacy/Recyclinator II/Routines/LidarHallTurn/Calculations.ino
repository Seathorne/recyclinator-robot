

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
// find hall distance and alignment for all 
//    pairs of lidar measurements  
int k;
int kk;
float sumY;
float sumTheta;
float YBar;
float ThetaBar;

  N = 0;  
  
  for (int i = 1; i < numII; i++)  {
    k = II[i];
    for (int j = (i+1); j < numII; j++ ) {
      N++;
      kk = II[j];
      D1 = D[k];
      alpha = angle[k];
      D2 = D[kk];
      beta = angle[kk];
      Serial.print(k);
      Serial.write(9);
      Serial.print(kk);
      Serial.write(9);

      Serial1.print(k);
      Serial1.write(9);
      Serial1.print(kk);
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

  sumY = 0;
  for (int i = 1; i < (N+1); i++) {
    sumY += Y[II[i]];
  }  
  YBar = sumY/numII;

  sumTheta = 0;
  for (int i = 1; i < (N+1); i++) {
    sumTheta += Theta[II[i]];
  }  
  ThetaBar = sumTheta/numII;

  Serial.print(" filter: YBar, ThetaBar  ");
  Serial.write(9);
  Serial.print(YBar,0);
  Serial.write(9);
  Serial.println(ThetaBar*radToDeg,1);  

  Serial1.print(" YBar, ThetaBar  ");
  Serial1.write(9);
  Serial1.print(YBar,0);
  Serial1.write(9);
  Serial1.println(ThetaBar*radToDeg,1);   
}

//--------------------------------------------------
void Filter() {
// save consistent, consecutive lidar distances
float diff[15];
int j;

// find difference between angle-adjacent lidar distances  
  for (int i = 1; i < num; i++)  {
    diff[i] = D[i+1] - D[i];   //starts at largest azimuth angle
    Serial.print(diff[i],0);
    Serial.write(9);
    
    Serial1.print(diff[i],0);
    Serial1.write(9);  
  }  
  Serial.println("  ");
  Serial1.println("  ");
// filter differences

    j = 1;
    numII = 0;
  for (int i = 1; i < num; i++)  {
    if ((diff[i] > 0) && (diff[i] < 100)) {   
      II[j] = i;                              //array of retained value indecies       
      Serial.print(II[j]);
      Serial.write(9);
      Serial1.print(II[j]);
      Serial1.write(9);
      j++;
      numII++;                               // number of retained values
    }
  }
  Serial.println("  ");
  Serial1.println("  ");

  Serial.print("  number of values:   ");
  Serial.print(numII);
  Serial.println("   ");

  Serial1.print(" number of values:  ");
  Serial1.print(numII);
  Serial1.println("   "); 
}

