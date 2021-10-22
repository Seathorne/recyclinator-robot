
/*   FUNCTIONS
     1.  void HallwayNavigation()  -  line   10
     2.  void WallFollow()         -  line   42
     3.  float angleLimit()        -  line   79
     4.  void wallLimit()          -  line   98
     5.  void FirstHall()          -  line  233
*/

void HallwayNavigation()  {

  if (FirstHallFlag == true) FirstHall();

  SideRange();                 //comparison measurements of different ranging sensors
  WallFollow();
  Encoders(encoderLt, encoderRt);

//  PrintMon();

//  Detect Hall End
     EndHallCheck();
     Print();
}
//---------------------------------------

/*
// Motor Speeds
            STOP    SLOW    MED     FAST
MtrSPEED    128     210     238     250
*/

void WallFollow() {

  angleLimit(angDel);    //wallAng set in SideRange() call to wallAngle()
  
  wallLimit();                           // wallDel set in wallLimit()
  Corr = int(wallDel + angDel + 0.5);     //round correction before added to speeds                                                                                                          

  RtMtrSpd = RtMtrSpeed;
  
  if (Dir == Right) {
    LtMtrSpd = LtMtrSpeed + Corr;      ;
  }
  if (Dir == Left) {
    LtMtrSpd = LtMtrSpeed - Corr;
  }

      if(LtMtrSpd >= (LtMtrSpeed + 7))
        LtMtrSpd = (LtMtrSpeed + 7);
      if(LtMtrSpd <= (LtMtrSpeed - 7))
        LtMtrSpd = (LtMtrSpeed - 7);       
 
  MtrSpeed(LtMtrSpd, RtMtrSpd);
}

//--------------------------------------
//-------------------------------------
void angleLimit(float &angDel) { 
  angDel = Ka * wallAng;  // Ka = 0.75 is slightly underdamped but approaches set point best

  if (angDel >= 8.0)
    angDel = 8.0;
  else if (angDel <= -8.0)
    angDel = -8.0;

  if (abs(wallAng) >= 25) {   
    angDel = 0;
  }     
}

//-------------------------------------
//-------------------------------------------------------
void wallLimit ()  {  
//  float featureDepth;
float farSide;
float nearSide;

  featureDepth = hallWidth - HW;

  if (featureDepth >= 200) {                   // cases where a sonar range too large for a hallway
    caseNum = 0;
    hallCase = "Long";
    wallDel = 0;
    angDel = 0;
    return;
  }

  if (Dir == Right)    {                        // RIGHT WALL FOLLOW
    nearSide = rangeRtF;
    farSide = rangeLtF;
  }
  else {                                    //LEFT WALL FOllow
    nearSide = rangeLtF;
    farSide = rangeRtF;
  }

  if (abs(featureDepth) <= 10)  {          // Case 1 - normal hall width
    caseNum = 1;
    hallCase = "Wall";                            // to within +/- 10 cm
    wallDistVal = 80;
  }

  else if ((featureDepth > 10) && (featureDepth < 55)) {
    if (nearSide > 90) {
      caseNum = 2;
      hallCase = "Shallow";                          // Case 2 = shallow recess near side
      wallDistVal = 80 + featureDepth;
    }
    else {
      caseNum = 3;
      hallCase = "FarRecess";                          // Case 3 = shallow recess far side
      wallDistVal = 80;
    }
  }

  else if ((featureDepth >= 55) && (featureDepth <= 80)) {
    if (nearSide > farSide)  {           // Case 4 = projection on far, recess on near side
      caseNum = 4;
      hallCase = "Recess/Proj";
      wallDistVal = 80 + featureDepth + 23;
    }
    else {
      caseNum = 5;
      hallCase = "Proj/Recess";                       // Case 5 = projection on near, recess on far side
      wallDistVal = 80 - 23;
    }
  }

  else if ((featureDepth > 80) && (featureDepth < 120)) {
    if (nearSide > farSide) {
      caseNum = 6;
      hallCase = "NearRecess";                        // Case 6 = recess near side
      wallDistVal = 80 + featureDepth;
    }
    if (farSide > nearSide) {             // Case 7 = recess on far side
      caseNum = 7;
      hallCase = "FarRecess";
      wallDistVal = 80;
    }
  }

  else if ((featureDepth > 120) && (featureDepth < 200)) {        // either extended recess or double recess
    if (nearSide > 200) {
      caseNum = 8;
      hallCase = "NearExt";                                             // Case 8 = extended recess on near side
      wallDistVal = 80 + featureDepth;
    }
    else if (nearSide < 200) {
      if (nearSide < 125) {
        caseNum = 9;
        hallCase = "FarExt";                      // Case 9 = extended recess on far side
        wallDistVal = 80;
      }
      else {
        caseNum = 10;
        hallCase  = "Double";                        // Case 10 = double recess
        wallDistVal = 80 + featureDepth / 2;
      }
    }
  }

  else if ((featureDepth < -10) && (featureDepth > -40)) {
    if (nearSide < 70)  {                  // Case 11 = projection on near side
      caseNum = 11;
      hallCase = "NearProj";
      wallDistVal = 80 + featureDepth;
    }
    else if (nearSide > 90) {            // Case 13 = projection on far side; shallow recees nearside
      caseNum = 13;
      hallCase = "Shallow/Proj";
      wallDistVal = 80 + 30;
    }
    else {
      caseNum = 12;
      hallCase = "FarProj";                       // Case 12 = projection on far side
      wallDistVal = 80;
    }
  }

  else if (featureDepth <= -40)  {         //  Case 14 = narrow hall opening
    caseNum = 14;
    hallCase = "Narrow";
    wallDistVal = 80 - 20;
  }

  else {                                  //  Case 15 = catch all
    caseNum = 15;
    hallCase = "None";
    wallDel = 0;
  }

  wallDel = Kp*(nearSide - wallDistVal);

  if (wallDel >= 8.0)
    wallDel = 8.0;
  else if (wallDel <= -8.0)
    wallDel = -8.0; 
}


//----------------------------------------






