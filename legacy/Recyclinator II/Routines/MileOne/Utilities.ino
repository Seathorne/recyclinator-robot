
void GyroTurn(byte &turnDir, int &angLimit)  {
    SetAcceleration(3);
//    MtrSpeed(MtrStop, MtrStop);
//    delay(100);                          //wait until robot stops before reading gyro    
    Serial3.write('Z');  
    delay(50); 
    while(Serial3.read() >= 0);  
    gyroAngle = 0;

    if (turnDir == Left) {                  //CCW Turn
      LtMtrSpd = MtrTurn;
      RtMtrSpd = MtrTurn + 20;      
    }
    else if (turnDir == Right) {            //CW turn
      LtMtrSpd = MtrTurn  + 20;
      RtMtrSpd = MtrTurn;         
    }
    else {                                //condition for straight ahead (turnDir = 2)       
      return;
    }
    Encoders(encoderLt, encoderRt);     //temp:  encoders after stop, before turn
    Serial1.print(encoderLt);
    Serial1.write(9);
    Serial1.println(encoderRt);

     lidarDist = Lidar();
     Serial1.print(" lidarDist =  ");
     Serial1.println(lidarDist);       
    
     do {       
       MtrSpeed(LtMtrSpd, RtMtrSpd);
       Serial3.write('G');  
       delay(20);
       if (Serial3.available() > 1 ) {
         gyroAngle = int(Serial3.read())<<8;
         gyroAngle += int(Serial3.read());
       }    
     } while (abs(gyroAngle) <= angLimit);   

     Serial1.print(" end gyro ");
     Serial1.println(gyroAngle);
      
     SetAcceleration(3);
     MtrSpeed(MtrStop, MtrStop);  
     delay(100);
      
     Serial3.write('G');  
     delay(20);
     if (Serial3.available() > 1 ) {
       gyroAngle = int(Serial3.read())<<8;
       gyroAngle += int(Serial3.read());
     }    
     Serial1.print(" stop gyro ");
     Serial1.println(gyroAngle);
     
}

//---------------------------------------------------
byte ConsecutiveTries(byte nTries) {
byte countFlag;

  if (ncount < nTries) {
    ncount++;
    countFlag = 0;
  }
  else {
    countFlag = 1;
    ncount = 0;
  }
  
  return countFlag;
}

