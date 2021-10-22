
void GyroTurn(byte &turnDir, int &angLimit)  {
    Serial3.write('Z');  
    delay(20); 
    while(Serial3.read() >= 0);  
    gyroAngle = 0;

    if (turnDir == Left) {                  //CCW Turn
      LtMtrSpd = MtrTurn;
      RtMtrSpd = MtrTurn+8;      
    }
    else if (turnDir == Right) {            //CW turn
      LtMtrSpd = MtrTurn+8;
      RtMtrSpd = MtrTurn;         
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
       Serial1.print( "gyroAngle   ");
       Serial1.println(gyroAngle);
     } while (abs(gyroAngle) <= angLimit);   

     SetAcceleration(5);
     MtrSpeed(MtrStop, MtrStop);  
     delay(500);
     SetAcceleration(3);
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
