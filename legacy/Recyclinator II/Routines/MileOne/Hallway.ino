/***************************************************************************************
                                           North
         ----------------------------------------------------------------------------|
         |              5                      6                         7           |
         |     __________________     ______________________      _______________    |
         |    |                  |    |                     |    |               |   |
         |    |                  |    |                     |    |               |   |             
         |    |                  |    |                     |    |               |   |
         |    |                  |    |                     |    |               |   |   
         |    |                  |    |                     |    |               |   |
         |    |                  |    |                     |    |               |   |
         | 1  |                  |  2 |                     |  3 |               | 4 |
         |    |                  |    |                     |    |               |   |
         |    |                  |    |                     |    |               |   |             
         |    |                  |    |                     |    |               |   |
         |    |                  |    |                     |    |               |   |   
         |    |                  |    |                     |    |               |   |
         |    |                  |    |                     |    |               |   |
         |    |                  |    |                     |    |               |   |
         |    |                  |    |                     |    |               |   |
         |    |__________________|    |_____________________|    |_______________|   |   
         |                                                                           |
         |            8                        9                       10            |
         ----------------------------------------------------------------------------                                                                           |
                     UAH   Engineering  Building  First Floor
***********************************************************************************/


/*   FUNCTIONS
     1.  boolean HallID()       -  line  38
     2.  void Stats()           -  line 239
     3.  void defineFeatureList -  line 418
     4.  void EndofHall()       -  line 472
     5.  void FirstHall()       -  line 425
     6.  void EndHallCheck()    -  line 448
     7.  void ChangeHall()      -  line 480
*/

boolean HallID()  {
//  Direction of travel:  hallDir:  1-N; 2-E; 3-S; 4-W  
//  End of hall turn:     turnDir:  0-Left (CCW); 1-Right(CW); 2-Straight

  switch (hallID) {
    case 1: {
      if((hallDir == North) &&  (turnDir == Right)) {
        hallID = 5;    
        hallDir = East;
        return true;
      }  
      else if ((hallDir == South) && (turnDir == Left)) {
        hallID = 8;
        hallDir = East;
        return true;
      }
      else {
        return false;
      }
      break;
    }
    
    case 2: {
      if((hallDir == North) && (turnDir == Left)) {
        hallID = 5;
        hallDir = West;
        return true;
      }        
      else if ((hallDir == South) && (turnDir == Left)) {
        hallID = 9;
        hallDir = East;
        return true;
      }
      else if ((hallDir == South) && (turnDir == Right)) {
        hallID = 8;
        hallDir = West;
        return true;
      }        
      else  {
        return false;
      }   
      break;  
    }
    
    case 3: {
      if((hallDir == North) &&  (turnDir == Right)) {
        hallID = 7;
        hallDir = East;
        return true;
      }        
      else if ((hallDir == South) && (turnDir == Left)) {
        hallID = 10;
        hallDir = East;
        return true;
      }
      else if ((hallDir == South) && (turnDir == Right)) {
        hallID = 9;
       hallDir = West;
       return true;
      } 
      else {
        return false;
      }     
      break;
    }
    
    case 4: {
      if((hallDir == North) && (turnDir == Left)) {
        hallID = 7;
        hallDir = West;
        return true;
      }        
      else if ((hallDir == South) && (turnDir == Right)) {
        hallID = 10;
        hallDir = West;
        return true;
      }
      else  {
        return false;
      }      
      break;
    }
    
    case 5: {
      if((hallDir == East) &&  (turnDir == Right)) {
        hallID = 2;
        hallDir = South;
        return true;
      }        
      else if ((hallDir == West) && (turnDir == Left)) {
        hallID = 1;
        hallDir = South;
        return true;
      } 
      else {
        return false;
      }  
      break;     
    }
    
    case 6: {
      return false;
      break;
    }
    
    case 7: {
      if((hallDir == East) &&  (turnDir == Right)) {
        hallID = 4; 
        hallDir = South;
        return true;
      } 
      else if ((hallDir == West) && (turnDir == Left)) {
        hallID = 3;
        hallDir = South;
        return true;
      }
      else {
        return false;
      }  
      break;    
    }
    
    case 8: {
      if((hallDir == East) && (turnDir == Left)) {
        hallID = 2;
        hallDir = North;
        return true;
      }    
      else if ((hallDir == East) && (turnDir == Straight)) {
        hallID = 9; 
        hallDir = East;
        return true;
      }      
      else if ((hallDir == West) && (turnDir == Right)) {
        hallID = 1;
        hallDir = North;
        return true;
      }
      else {
        return false;
      }   
      break;   
   } 
  
    case 9: {
      if((hallDir == East) && (turnDir == Left)) {
        hallID = 3;
        hallDir = North;
        return true;
      }  
      else if ((hallDir == East) && (turnDir == Straight)) {
        hallID = 10; 
        hallDir = Straight;
        return true;
      }      
      else if ((hallDir == West) && (turnDir == Right)) {
        hallID = 2;
        hallDir = North;
        return true;
      }
      else if ((hallDir == West) && (turnDir == Straight)) {
        hallID = 8;
        hallDir = West; 
        return true;
      }
      else {
        return false;
      }
      break;      
    }
    
    case 10: {
      if((hallDir == East) && (turnDir == Left)) {
        hallID = 4;
        hallDir = North;
        return true;
      }
      else if ((hallDir == East) && (turnDir == Straight)) {
        return false;
      }      
      else if ((hallDir == West) && (turnDir == Right)) {
        hallID = 3;
        hallDir = North;
        return true;
      } 
      else if ((hallDir == West) && (turnDir == Straight)) {
        hallID = 9; 
        hallDir = West;
        return true;
      } 
      else {
        return false;
      }    
      break; 
    }
  }
  return false;
}

//---------------------------------------------------------------
void Stats()  {
//  HW:  hallway width; 241 except for hall 4, which is 214;  hall 6 and default is zero, which indicates an error.
//  hallDir (hall travel direction): 1-N, 2-E, 3-S, 4-W
//  Dir:  which side of hall to follow with offset, 0-left, 1-right
// *****  major change for Recylinator II - eliminate hallAdvCenterEnc, hallEndEnc, hall 45AdvEnc  *******

  Serial1.print("  HallStats  ID = ");
  Serial1.println(hallID);  

  featureIndex = 0;
  
  switch (hallID) {
    case 1: {
      HW = 241;
      hallLengthEnc = 76000;     // enc between shortest straight walls   
      hallEndEnc = 60400;   

      if(hallDir == North) {
       byte feature[] = {1,6,1,6,1,99};    
       defineFeatureList(feature, sizeof(feature));  
        Dir = Left;
      }
      else {
        byte feature[] = {1,6,0,1,6,1,99};         
       defineFeatureList(feature, sizeof(feature));          
        Dir = Right;
      }
      break;
    }
    
    case 2: {
      HW = 241;
       hallLengthEnc = 84000;   
       hallEndEnc = 67000;
         
      if(hallDir == North) {
        Serial1.println(  "stats  case 2,  dir North ");
        byte feature[] = {1,6,1,7,1,10,1,99};              
        defineFeatureList(feature, sizeof(feature));
        Dir = Right;
      }
      else {
        byte feature[] = {1,10,1,6,1,7,1,99};
        defineFeatureList(feature, sizeof(feature));
        Dir = Right;        
      }  
      break;    
    }
    
    case 3: {
      HW = 241;
      hallLengthEnc = 84000;  
       
      if(hallDir == North) {
        byte feature[] = {1,10,5,10,1,11,1,10,5,7,1,99};   
        defineFeatureList(feature, sizeof(feature));     
        Dir = Left;        
      }
      else {
        byte feature[] = {1,7,5,10,1,11,1,10,5,10,1,99};   
        defineFeatureList(feature, sizeof(feature));     
        Dir = Right;
      }
      break;      
    }
    
    case 4: {
      HW = 214;
      hallLengthEnc = 92000;    
        
      if(hallDir == North) {
        byte feature[] = {12,1,7,12,1,9,12,1,3,1,12,1,12,99};  
        defineFeatureList(feature, sizeof(feature));      
        Dir = Left;
      }
      else {
        byte feature[] = {12,1,12,1,9,1,12,99};  
        defineFeatureList(feature, sizeof(feature));      
        Dir = Right;
      }
      break;
    }
    
    case 5: {
      HW = 241;
      hallLengthEnc = 67000;   
      hallEndEnc = 55000;
        
      if(hallDir == West) {
        byte feature[] = {1,6,8,1,0,1,99};        
        defineFeatureList(feature, sizeof(feature));  
        Dir = Right;
      }
      else {
        byte feature[] = {1,8,1,99};
        defineFeatureList(feature, sizeof(feature));        
        Dir = Left;
      }
      break;      
    }
    
    case 6: {
      break;
    }
    
    case 7: {
      HW = 241;
      hallLengthEnc = 39000;    
        
      if(hallDir == West) {
       byte feature[] = {1,12,1,3,99};       
       defineFeatureList(feature, sizeof(feature)); 
        Dir = Right;        
      }
      else {
        byte feature[] = {1,12,99}; 
        defineFeatureList(feature, sizeof(feature));       
        Dir = Left;        
      }   
      break;  
    }
    
    case 8: {
      HW = 241;
      hallLengthEnc = 54000;    
      hallEndEnc = 54000;
       
      if(hallDir == West) {
        byte feature[] = {1,7,6,1,6,1,99};      
        defineFeatureList(feature, sizeof(feature));  
        Dir = Right;
      }
      else {
        byte feature[] = {1,7,1,99};        
        defineFeatureList(feature, sizeof(feature));
        Dir = Right;
      }  
      break;      
    } 
    
    case 9: {
      HW = 241;
      hallLengthEnc = 71000;      
     
      if(hallDir == West) {
        byte feature[] = {1,12,14,1,2,1,99};   
        defineFeatureList(feature, sizeof(feature));     
        Dir = Left;        
      }
      else {
        byte feature[] = {1,2,1,11,14,12,1,1,14,13,1,99};   
        defineFeatureList(feature, sizeof(feature));     
        Dir = Right;        
      } 
      break;     
    }
    
    case 10: {
      HW = 241;
      hallLengthEnc = 38000;      
    
      if(hallDir == West) {
        byte feature[] = {1,12,1,6,99};        
        defineFeatureList(feature, sizeof(feature));
        Dir = Left;        
      }
      else {
        byte feature[] = {6,1,12,1,99};        
        defineFeatureList(feature, sizeof(feature));
        Dir = Left;        
      }
      break;      
    }
    
    default: {
      HW = 0;
    }
  }
 
}

//----------------------------------------------------
void defineFeatureList(byte feature[], byte N) {
  for (int i = 0; i < N; i++) {
    featureList[i] = feature[i]; 
  }  
}

//---------------------------------------
void FirstHall()  {   

  Serial1.print(" hallID, hallDir  ");
  Serial1.write(9);
  Serial1.print(hallID);
  Serial1.write(9);
  Serial1.println(hallDir);
    
  SideRange();
  MtrSpeed(MtrSlow, MtrSlow);    
  
  while (hallWidth > 250) {     
      SideRange(); 
      Encoders(encoderLt, encoderRt); 
      Print();
   }
   EncRst();
   Encoders(encoderLt, encoderRt);
   Serial1.println("  beginning of first hall  ");
   FirstHallFlag = false;
} 

//---------------------------------------------------
void EndHallCheck() {     
byte featureType;

  featureType = featureList[featureIndex];
   
  if (featureType == 99) {
    CrossHallRange();
    Serial1.print("  CrossHall Ranges   ");  
    Serial1.print(rangeLtHall,0);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
    Serial1.write(9);
    Serial1.println(rangeRtHall,0);
    
    if (endHallWidth > 250) {
       Serial1.print("   endHallWidth  =  ");
       Serial1.println(endHallWidth);
       
       lidarDist = Lidar();
       Serial1.print(" lidarDist =  ");
       Serial1.println(lidarDist);       
       
       EndofHall(); 

//      MtrSpeed(MtrStop, MtrStop);
//      delay(50);
    }
  }
  else if (featureType == caseNum) {
    byte countsFlag = ConsecutiveTries(3);
    Serial1.print("  feature tries ");
    Serial1.println(ncount);
    if (countsFlag == 1) {
      featureIndex++;                 // look for next feature
    }                                 // ncount initialization in setup()
  }
}

//---------------------------------------------------
void EndofHall() {
  Serial1.println(" end of hall ");   
  In_Hallway = false;   
  At_Turn_Node = true;
} 

//---------------------------------------------------------
void ChangeHall()   {
   Serial1.println("  SetUp ChangeHall  ");   
// 1. Choose Turn Direction  
  turnDir = turnHall2North[iTurn];          //decide which way to turn; ii initialized in set-up
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
      angLimit = 80;    
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
    EncRst();        
//  digitalWrite(LtTurnSig_pin, LOW);
//  digitalWrite(RtTurnSig_pin, LOW);  
   
  Stats();                               //update stats for new hallway  

  At_Turn_Node = false;
  In_Hallway = true;
  Serial1.println("  end ChangeHall  ");     
} 



