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
     1.  boolean HallID()  -  line 35
     2.  void Stats()      -  line 237
     3.  void EndOfHall()  -  line 452
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

//------------------------------------------------
//--------------------------------------------------

void Stats()  {
//  HW:  hallway width; 241 except for hall 4, which is 214;  hall 6 and default is zero, which indicates an error.
//  hallDir (hall travel direction): 1-N, 2-E, 3-S, 4-W
//  Dir:  which side of hall to follow with offset, 0-left, 1-right
// *****  major change for Recylinator II - eliminate hallAdvCenterEnc, hallEndEnc, hall 45AdvEnc  *******

  Serial1.print("  HallStats  ID = ");
  Serial1.print(hallID);  

  featureIndex = 0;
  
  switch (hallID) {
    case 1: {
      HW = 241;
      hallLengthEnc = 76000;     // enc between shortest straight walls      

      if(hallDir == North) {
       byte feature[] = {1,11,1,6,1,7,5,6,1,11,1,99};    
       defineFeatureList(feature);  
        Dir = Left;
      }
      else {
        byte feature[] = {1,11,1,6,0,7,5,7,1,6,1,99};         
       defineFeatureList(feature);          
        Dir = Right;
      }
      break;
    }
    
    case 2: {
      HW = 241;
       hallLengthEnc = 84000;   
         
      if(hallDir == North) {
        Serial1.println(  "stats  case 2,  dir North ");
        byte feature[] = {1,6,4,1,7,12,1,10,12,1,0,99};           
        defineFeatureList(feature);
        Dir = Right;
      }
      else {
        byte feature[] = {1,11,10,1,11,1,6,1,5,7,1,99};
        defineFeatureList(feature);
        Dir = Right;        
      }  
      break;    
    }
    
    case 3: {
      HW = 241;
      hallLengthEnc = 84000;  
       
      if(hallDir == North) {
        byte feature[] = {1,10,5,10,1,11,1,10,5,7,1,99};   
        defineFeatureList(feature);     
        Dir = Left;        
      }
      else {
        byte feature[] = {1,7,5,10,1,11,1,10,5,10,1,99};   
        defineFeatureList(feature);     
        Dir = Right;
      }
      break;      
    }
    
    case 4: {
      HW = 214;
      hallLengthEnc = 92000;    
;        
      if(hallDir == North) {
        byte feature[] = {12,1,7,12,1,9,12,1,3,1,12,1,12,99};  
        defineFeatureList(feature);      
        Dir = Left;
      }
      else {
        byte feature[] = {12,1,12,1,9,1,12,99};  
        defineFeatureList(feature);      
        Dir = Right;
      }
      break;
    }
    
    case 5: {
      HW = 241;
      hallLengthEnc = 67000;   
        
      if(hallDir == West) {
        byte feature[] = {1,12,1,6,8,2,3,1,0,1,99};      
        defineFeatureList(feature);  
        Dir = Right;
      }
      else {
        byte feature[] = {1,0,1,9,7,1,11,99};
        defineFeatureList(feature);        
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
       defineFeatureList(feature); 
        Dir = Right;        
      }
      else {
        byte feature[] = {1,12,99}; 
        defineFeatureList(feature);       
        Dir = Left;        
      }   
      break;  
    }
    
    case 8: {
      HW = 241;
      hallLengthEnc = 66000;    
       
      if(hallDir == West) {
        byte feature[] = {13,1,7,6,1,8,1,14,99};      
        defineFeatureList(feature);  
        Dir = Right;
      }
      else {
        byte feature[] = {14,1,9,3,1,7,6,1,99};        
        defineFeatureList(feature);
        Dir = Right;
      }  
      break;      
    } 
    
    case 9: {
      HW = 241;
      hallLengthEnc = 71000;      
     
      if(hallDir == West) {
        byte feature[] = {1,12,14,1,2,1,99};   
        defineFeatureList(feature);     
        Dir = Left;        
      }
      else {
        byte feature[] = {1,2,1,11,14,12,1,1,14,13,1,99};   
        defineFeatureList(feature);     
        Dir = Right;        
      } 
      break;     
    }
    
    case 10: {
      HW = 241;
      hallLengthEnc = 38000;      
    
      if(hallDir == West) {
        byte feature[] = {1,12,1,6,99};        
        defineFeatureList(feature);
        Dir = Left;        
      }
      else {
        byte feature[] = {6,1,12,1,99};        
        defineFeatureList(feature);
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
void defineFeatureList(byte feature[]) {
  for (int i = 0; i < int(sizeof(feature))/sizeof(int); i++) {
    featureList[i] = feature[i]; 
  }  
  Serial.println("   ");
}

//---------------------------------------------------
void EndofHall() {
  Serial1.println(" end hall ");   
  In_Hallway = false;  
      MtrSpeed(MtrStop, MtrStop);  
//  At_Turn_Node = true;
} 

//---------------------------------------
void FirstHall()  {   

  Serial1.print(" hallID, hallDir  ");
  Serial1.write(9);
  Serial1.print(hallID);
  Serial1.write(9);
  Serial1.println(hallDir);
    
  SideRange();
  MtrSpeed(MtrMed, MtrMed);    
  
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
void EndHallCheck(byte featureList[]) {     
byte featureType;
  Serial.println(sizeof(featureList));
  for (int i = 0; i < int(sizeof(featureList))/sizeof(int); i++) {
    Serial.print(featureList[i]);
  }
  featureType = featureList[featureIndex];
  Serial.print(" Index  = ");
  Serial.print(featureIndex);  
  Serial.print("     featureType   ");
  Serial.print(featureType);
  Serial.print("        caseNum  = ");
  Serial.println(caseNum); 
   
  if (featureType == 99) {
    CrossHallRange();  
    Serial1.print(rangeLtHall,0);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
    Serial1.write(9);
    Serial1.println(rangeRtHall,0);
    
    if (endHallWidth > 250) {
       Serial1.print("   endHallWidth  =  ");
       Serial1.println(endHallWidth);
       EndofHall();  
      }
    }
  else if (featureType == caseNum) {
    featureIndex++;
  }
}



