
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
      Serial.print(II[j]);
      Serial.write(9);      
      Serial1.print(II[j]);
      Serial1.write(9);      
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

  Serial.write(9);
  Serial.println(" gaps fwd scan  ");
  Serial1.write(9);
  Serial1.println("  gaps fwd scan");
  for (int i = 2; i <= 4; i++)  {    // forward scan: toward smaller angles;
    if (II[i] == 0) {
      for (int m = i; m >= 1; m--) {
        II[m] = 0;
      }
    }
  }
  Serial.println("  ");
  Serial.print(II[1]);
  Serial.write(9);
  Serial1.print(II[1]);
  Serial1.write(9);
  for (int i = 2; i <= 4; i++) {
    Serial.print(II[i]);
    Serial.write(9);
    Serial1.print(II[i]);
    Serial1.write(9);
  }

  Serial.println("  ");
  Serial1.println("   ");
  Serial.println("  gaps rev scan  ");
  Serial1.println("  gaps rev scan  ");
  
  for (int i = num-1; i >= 6; i--)  {    // rev scan
    if (II[i] == 0) 
      for (int j = i; j <num; j++) {
        II[j] = 0;
      }    
  }

  for (int i = num-1; i >= 6; i--) {
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
Serial.print("  numJJ = ");
Serial.println(numJJ);
  Serial.println("  ");
  Serial1.println("  ");
}

//--------------------------------------------------
void Pairs() {
// find hall distance and alignment for all 
//    pairs of lidar measurements  
int k;
int kk;

  N = 0; 
  Serial.print(" N0 = ");
Serial.println(N);  
  for (int i = 1; i < numJJ; i++)  {
    k = JJ[i];
    for (int j = (i+1); j <= numJJ; j++ ) {
      N++;
      kk = JJ[j];
      if (dir == 0) {
        D1 = D[k];
        alpha = angle[k];
        D2 = D[kk];
        beta = angle[kk];
      }
      else {              //for right scans alpha < beta, reverse angles and 
        D2 = D[k];        //  corresponding distances
        beta = angle[k];
        D1 = D[kk];
        alpha = angle[kk];        
      }
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
    Serial.print(" N1 = ");
Serial.println(N);
  }
}

//--------------------------------
void Average()  {  
float sumY;
float sumTheta;
float YBar;
float ThetaBar;
Serial.print(" N2 = ");
Serial.println(N);
  sumY = 0;
  for (int i = 1; i <= N; i++) {
    sumY += Y[i];
    Serial.print(i);
    Serial.write(9);
    Serial.print(Y[i]);
    Serial.write(9);
    Serial.println(sumY);
  }  
  YBar = sumY/N;

  sumTheta = 0;
  for (int i = 1; i <= N; i++) {
    sumTheta += Theta[i];
  }  
  ThetaBar = sumTheta/N;

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

//------------------------------------------------------
void Compute()  {
 float temp1;
 float temp2;

//   angles alpha and beta (deg) measured CW from left perpendicular to heading
//   theta (rad) measured positive CW from heading
  if(dir == 0) {
    temp1 = D1*sin(alpha/radToDeg) - D2*sin(beta/radToDeg);
    temp2 = D2*cos(beta/radToDeg) - D1*cos(alpha/radToDeg);
  }
  else {
    temp1 = -D1*sin(alpha/radToDeg) + D2*sin(beta/radToDeg);
    temp2 = D2*cos(beta/radToDeg) - D1*cos(alpha/radToDeg);    
  }
  theta = atan2(temp1, temp2);

  y = D1*(sin(alpha/radToDeg)*cos(theta) + cos(alpha/radToDeg)*sin(theta));
}
