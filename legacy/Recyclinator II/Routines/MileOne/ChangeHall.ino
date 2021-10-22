void ChangeHall()   {
   Serial1.println("  SetUp ChangeHall  ");   
// 1. Choose Turn Direction  
  turnDir = turnHall2North[iTurn];             //decide which way to turn; ii initialized in set-up
  do {     
    if(turnDir == 3) {                      // end of turn direction array reached
      MtrSpeed(MtrStop, MtrStop);
      while(1) {
       Serial1.println(" turn = 3");
       delay(50);
      }
    }
    ID = HallID();                      //sets new hallway ID and hall direction; initialized in SetUp                           
  } while (ID == false);                // checks when turn dir chosen randomly and turn dir not allowed

  Serial1.print(" hallID, hallDir  ");
  Serial1.write(9);
  Serial1.print(hallID);
  Serial1.write(9);
  Serial1.println(hallDir);                        
    iTurn++;          

    while(1) {
      MtrSpeed(MtrTurn, MtrTurn+8);
      Encoders(encoderLt, encoderRt);
      Serial1.print(encoderLt);
      Serial1.write(9);
      Serial1.println(encoderRt);

      if(turnDir == 0) {
        angLimit = 90;    
        GyroTurn(turnDir, angLimit); 
     
        Serial3.write('Z');  
        delay(5);
        while(Serial3.read() >= 0);  
        gyroAngle = 0;  
      }
    }
/*        
    
/// 6.  Look for new hallway wall
    SetAcceleration(1);
    EncRst();
    SideRange();
    CrossHallRange();
//    forwardRange();    
    MtrSpeed(MtrSlow, MtrSlow);
   
   while (hallWidth > 250) { 
      GetEncoders();
//      Encoders();
      SideRange();
      CrossHallRange();
//      forwardRange();
      Print();
   }  
    EncRst();        
//  digitalWrite(LtTurnSig_pin, LOW);
//  digitalWrite(RtTurnSig_pin, LOW); 
*/ 
   
  Stats();                    //update stats for new hallway  

  At_Turn_Node = false;
  In_Hallway = true;
  Serial1.println("  end ChangeHall  ");     
} 


