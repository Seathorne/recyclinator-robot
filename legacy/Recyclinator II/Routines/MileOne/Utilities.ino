
void GyroTurn(byte &turnDir, int &angLimit)  {
    SetAcceleration(3);
    MtrSpeed(MtrStop, MtrStop);
    delay(500);                          //wait until robot stops before reading gyro    
    Serial3.write('Z');  
    delay(20); 
    while(Serial3.read() >= 0);  
    gyroAngle = 0;

    if (turnDir == Left) {                  //CCW Turn
      LtMtrSpd = MtrSlow;
      RtMtrSpd = MtrSlow+24;      
    }
    else if (turnDir == Right) {            //CW turn
      LtMtrSpd = MtrSlow+24;
      RtMtrSpd = MtrSlow;         
    }
    else {                                //condition for straight ahead (turnDir = 2)       
      return;
    }

     do {       
       MtrSpeed(LtMtrSpd, RtMtrSpd);
       Serial3.write('G');  
       delay(20);
       if (Serial3.available() > 1 ) {
         gyroAngle = int(Serial3.read())<<8;
         gyroAngle += int(Serial3.read());
       }    
     } while (abs(gyroAngle) <= angLimit);  

      Serial1.print(" end gyro angle ");
      Serial1.println(gyroAngle);

     SetAcceleration(3);
     MtrSpeed(MtrStop, MtrStop);  
     delay(500);
       Serial3.write('G');  
       delay(20);
       if (Serial3.available() > 1 ) {
         gyroAngle = int(Serial3.read())<<8;
         gyroAngle += int(Serial3.read());
       }         

      Serial1.print(" stop gyro angle ");
      Serial1.println(gyroAngle);       
}

//---------------------------------------------------
byte ConsecutiveTries(byte nTries) {
byte ncount;
byte flag;
  
  if (ncount < nTries) {
    ncount++;
    flag = 0;
  }
  else {
    ncount = 0;
  }
  if (ncount == nTries)
    flag = 1;
  return flag;
}
