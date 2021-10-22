
void GyroTurn(byte &turnDir)  {
    if (turnDir == Left) {                  //CCW Turn
      LtMtrSpd = MtrStop;
      RtMtrSpd = MtrTurn;      
    }
    else if (turnDir == Right) {            //CW turn
      LtMtrSpd = MtrTurn;
      RtMtrSpd = MtrStop;         
    }
    else {                                //condition for straight ahead (turnDir = 2)       
      return;
    }
       Serial3.write('G');  
       delay(20);
       if (Serial3.available() > 1 ) {
         gyroAngle = int(Serial3.read())<<8;
         gyroAngle += int(Serial3.read());
       }    
}

//----------------------------------

