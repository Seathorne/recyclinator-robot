

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

  N = 0;   
  for (int i = 1; i < numJJ; i++)  {
    k = JJ[i];
    for (int j = (i+1); j <= numJJ; j++ ) {
      N++;
      kk = JJ[j];
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
}

//--------------------------------
void Average()  {  
float sumY;
float sumTheta;
float YBar;
float ThetaBar;

  sumY = 0;
  for (int i = 1; i <= N; i++) {
    sumY += Y[JJ[i]];
  }  
  YBar = sumY/numJJ;

  sumTheta = 0;
  for (int i = 1; i <= N; i++) {
    sumTheta += Theta[JJ[i]];
  }  
  ThetaBar = sumTheta/numJJ;

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
void FilterDistances() {
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

    j = 0;
    numII = 0;
  for (int i = 1; i < num; i++)  {
    j++;
    if ((diff[i] > 0) && (diff[i] < 100)) {   
      II[j] = i;                                    
      Serial.print(II[j]);
      Serial.write(9);
      Serial1.print(II[j]);
      Serial1.write(9);
    }
    else {
      II[j] = 0;
    }
  }
  Serial.println("  ");
  Serial1.println("  ");

  Serial.print("  # diff():   ");
  Serial.print(j);
  Serial.println("   ");

  Serial1.print(" # diff():  ");
  Serial1.print(j);
  Serial1.println("   "); 
}

//--------------------------------
void FilterGaps()  {
int jj;

  Serial.println(" gaps fwd scan  ");
  Serial1.println("  gaps fwd scan");
  for (int i = 2; i < num; i++)  {    // forward scan
    if (II[i] == 0) {
      II[i-1] = 0;
    }
  }

  for (int i = 2; i < num; i++) {
    Serial.print(II[i]);
    Serial.write(9);
    Serial1.print(II[i]);
    Serial1.write(9);
  }

  Serial.println("  ");
  Serial1.println("   ");
  Serial.println("  gaps rev scan  ");
  Serial1.println("  gaps rev scan  ");
  
  for (int i = num-2; i >= 1; i--)  {    // rev scan
    if (II[i] == 0) 
      II[i+1] = 0;
  }

  for (int i = num-2; i >= 1; i--) {
    Serial.print(II[i]);
    Serial.write(9);
    Serial1.print(II[i]);
    Serial1.write(9);
  }

  Serial.println("   ");
  Serial1.println("  ");
  Serial.println(" final filter ");
  Serial1.println(" final filter ");

  jj = 1;
  numJJ = 0;
  for (int i = 1; i < num; i++) {
    if (II[i] != 0) {
      JJ[jj] = II[i];
      jj++;
      numJJ++;
    }
  }  

  for (int i = 1; i <= numJJ; i++) {
    Serial.print(JJ[i]);
    Serial.write(9);
    Serial1.print(JJ[i]);
    Serial1.write(9);
  }

  Serial.println("  ");
  Serial1.println("  ");
}

