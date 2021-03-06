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

    Encoders(encoderLt, encoderRt);
    Serial1.print(encoderLt);
    Serial1.write(9);
    Serial1.println(encoderRt);
    
//  2.  Make 90 deg hall turn (CCW is negative angle)
    if(turnDir != 3) {
      angLimit = 75;    
      GyroTurn(turnDir, angLimit); 
    }
    
      Serial3.write('Z');  
      delay(5);
      while(Serial3.read() >= 0);  
      gyroAngle = 0;         
    
// 3.  Look for new hallway wall
    SetAcceleration(3);
    EncRst();
    SideRange();
    CrossHallRange();    
    MtrSpeed(MtrSlow, MtrSlow);
   
   while (hallWidth > 250) { 
      Encoders(encoderLt, encoderRt);
      SideRange();
      CrossHallRange();
      Print();
   }  
   Serial1.println("  new hall ");
    EncRst();        
//  digitalWrite(LtTurnSig_pin, LOW);
//  digitalWrite(RtTurnSig_pin, LOW); 
 
   
  Stats();                    //update stats for new hallway  

  At_Turn_Node = false;
  In_Hallway = true;
  Serial1.println("  end ChangeHall  ");     
} 


