void ChangeHall()   {
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
  
   Serial1.println("  SetUp ChangeHall  "); 
//  Left Turns - Lt motor speed turn; Rt motor speed slow

    while(1) {
      MtrSpeed(MtrTurn, MtrTurn+8);
    }

/*        

//  2.  Advance after end of hall
//   MtrSpeed(MtrStop, MtrStop);  

    if(turnDir == 0) {
      digitalWrite(LtTurnSig_pin, HIGH);            //turn signal lights
      digitalWrite(RtTurnSig_pin, LOW);   
    }
    else if (turnDir == 1) {
      digitalWrite(LtTurnSig_pin, LOW);
      digitalWrite(RtTurnSig_pin, HIGH);        
    }
    else if (turnDir == 2) {
      digitalWrite(LtTurnSig_pin, HIGH);
      digitalWrite(RtTurnSig_pin, HIGH);        
    }
    
    
    EncRst(); 
    GetEncoders();
//    Encoders();
    MtrSpeed(MtrMed, MtrMed);
    
    do {        
      GetEncoders();
//      Encoders();
      Print();   
    } while (encoderLt <= hallAdvCenterEnc);      

//  3.  Turn 45 degrees
  if(turnDir != 2) {

  
//  4.  Advance to middle of hall  
    EncRst();
    SetAcceleration(1);     
    MtrSpeed(MtrSlow, MtrSlow);

 

//  5.  Turn 45 degrees

  }

  else if (turnDir == 2) {          //when no turn, advance far enough to see open hall
    EncRst(); 
    GetEncoders();
//      Encoders();
    MtrSpeed(MtrSlow, MtrSlow);
    
    do {                                                       
      GetEncoders();
//      Encoders();
      Print();    
    } while (encoderLt <= hallAdvCenterEnc + 2000);   
  }
    
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
  Serial1.println("  end ChangeHall  ");     
} 


