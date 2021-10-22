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

//--------------------------------------------------
//-------------------------------------------------
//----------------------------------------------------------------------
void Stats()  {
//  HW:  hallway width; 241 except for hall 4, which is 214;  hall 6 and default is zero, which indicates an error.
//  hallDir (hall travel direction): 1-N, 2-E, 3-S, 4-W
//  Dir:  which side of hall to follow with offset, 0-left, 1-right
// endWidth and endEnc,  when these together exceed the values, the end of the hall has been reached.
/*
  switch (hallID) {
    case 1: {
      HW = 241;
      if(hallDir == North) {
        byte featureList[] = {1,11,1,6,1,7,5,6,1,11,1};        
        Dir = Left;
        hallLengthEnc = 76000;     // enc between shortest straight walls
        hallAdvCenterEnc = 500;      // enc distance to advance after end of hall
        hallEndEnc = 1000;        // enc from last open door to end straight wall
        hall45AdvEnc = 5000;      // enc advance after first 45 deg turn
      }
      else {
        byte featureList[] = {1,11,1,6,0,7,5,7,1,6,1};         
        Dir = Right;
        hallLengthEnc = 76000;
        hallAdvCenterEnc = 8000;
        hallEndEnc = 600;
        hall45AdvEnc = 5000;        
      }      
      break;
    }
    
    case 2: {
      HW = 241;
      if(hallDir == North) {
        byte featureList[] = {1,7,5,1,6,1,11,1,10,1};          
        Dir = Right;
        hallLengthEnc = 84000;
        hallAdvCenterEnc = 500;
        hallEndEnc = 600;
        hall45AdvEnc = 5000;
      }
      else {
        byte featureList[] = {1,11,10,1,11,1,6,1,5,7,1};
        Dir = Right;        
        hallLengthEnc = 84000;
        hallAdvCenterEnc = 500;
        hallEndEnc = 850;
        hall45AdvEnc = 5000;
      }  
      break;    
    }
    
    case 3: {
      HW = 241;
      if(hallDir == North) {
        byte featureList[] = {1,10,5,10,1,11,1,10,5,7,1};        
        Dir = Left;        
        hallLengthEnc = 84000;
        hallAdvCenterEnc = 500;
        hallEndEnc = 350;
        hall45AdvEnc = 5000;
      }
      else {
        byte featureList[] = {1,7,5,10,1,11,1,10,5,10,1};        
        Dir = Right;
        hallLengthEnc = 84000;
        hallAdvCenterEnc = 500;
        hallEndEnc = 450;
        hall45AdvEnc = 3000;
      }
      break;      
    }
    
    case 4: {
      HW = 214;
      if(hallDir == North) {
        byte featureList[] = {12,1,7,12,1,9,12,1,3,1,12,1,12};        
        Dir = Left;
        hallLengthEnc = 92000;
        hallAdvCenterEnc = 500;
        hallEndEnc = 350;
        hall45AdvEnc = 2000;
      }
      else {
        byte featureList[] = {12,1,12,1,9,1,12};        
        Dir = Right;
        hallLengthEnc = 92000;
        hallAdvCenterEnc = 100;
        hallEndEnc = 5000;
        hall45AdvEnc = 500;
      }
      break;
    }
    
    case 5: {
      HW = 241;
      if(hallDir == West) {
        byte featureList[] = {1,12,1,6,8,2,3,1,0,1};        
        Dir = Right;
        hallLengthEnc = 67000;
        hallAdvCenterEnc = 500;
        hallEndEnc = 550;
        hall45AdvEnc = 4500;
      }
      else {
        byte featureList[] = {1,0,1,9,7,1,11};        
        Dir = Left;
        hallLengthEnc = 67000;
        hallAdvCenterEnc = 500;
        hallEndEnc = 950;
        hall45AdvEnc = 5000;
      }
      break;      
    }
    
    case 6: {
      break;
    }
    
    case 7: {
      HW = 241;
      if(hallDir == West) {
        byte featureList[] = {1,12,1,3};        
        Dir = Right;        
        hallLengthEnc = 39000;
        hallAdvCenterEnc = 2500;
        hallEndEnc = 800;
        hall45AdvEnc = 3000;
      }
      else {
        byte featureList[] = {1,12};        
        Dir = Left;        
        hallLengthEnc = 39000;
        hallAdvCenterEnc = 0;
        hallEndEnc = 550;
        hall45AdvEnc = 0;
      }   
      break;  
    }
    
    case 8: {
      HW = 241;
      if(hallDir == West) {
        byte featureList[] = {13,1,7,6,1,8,1,14};        
        Dir = Right;
        hallLengthEnc = 66000;
        hallAdvCenterEnc = 500;
        hallEndEnc = 550;
        hall45AdvEnc = 4500;
      }
      else {
        byte featureList[] = {14,1,9,3,1,7,6,1};        
        Dir = Right;
        hallLengthEnc = 66000;
        hallAdvCenterEnc = 500;
        hallEndEnc = 450;
        hall45AdvEnc = 4500;
      }  
      break;      
    } 
    
    case 9: {
      HW = 241;
      if(hallDir == West) {
        byte featureList[] = {1,12,14,1,2,1};        
        Dir = Left;        
        hallLengthEnc = 71000;
        hallAdvCenterEnc = 0;
        hallEndEnc = 350;
        hall45AdvEnc = 0;
      }
      else {
        byte featureList[] = {1,2,1,11,14,12,1,1,14,13,1};        
        Dir = Right;        
        hallLengthEnc = 71000;
        hallAdvCenterEnc = 500;
        hallEndEnc = 550;
        hall45AdvEnc = 3500;
      } 
      break;     
    }
    
    case 10: {
      HW = 241;
      if(hallDir == West) {
        byte featureList[] = {1,12,1,6};        
        Dir = Left;        
        hallLengthEnc = 38000;
        hallAdvCenterEnc = 500;
        hallEndEnc = 1200;
        hall45AdvEnc = 5500;
      }
      else {
        byte featureList[] = {6,1,12,1};        
        Dir = Left;        
        hallLengthEnc = 38000;
        hallAdvCenterEnc = 500;
        hallEndEnc = 3000;
        hall45AdvEnc = 0;
      }
      break;      
    }
    
    default: {
      HW = 0;
    }
  }
  

//re-zero feature list for new hall ID
//  iFeature = 0;                  //position index for a hall's feature list      

*/
Serial1.println("  Hallway Stats");  
}

//-----------------------------------------------------
//---------------------------------------------------
void EndofHall() {
  Serial1.println(" end hall ");   
  In_Hallway = false;  
      MtrSpeed(MtrStop, MtrStop);  
//  At_Turn_Node = true;
} 
