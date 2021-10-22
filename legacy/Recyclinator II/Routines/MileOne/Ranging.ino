
/*   FUNCTIONS
     1.  void SideRange()        -  line  13
     2.  void frontSideRange()   -  line  35
     3.  void rearSideRange()    -  line  51
     4.  void CrossHallRange()   -  line  66
     5.  void HallRangeLT()      -  line  74
     6.  void HallRangeRt()      -  line  82
     7.  float wallAngle()       -  line  90
     8.  void pulseOut()         -  line 109
*/

void SideRange() {
  float rangeRtDiff;
  float rangeLtDiff;
  
  frontSideRange();
  rearSideRange();  

  if (Dir == Right) {
    rangeRtDiff = (rangeRtF - rangeRtR);
    wallAng = wallAngle(rangeRtDiff);
  } 
  else {
    rangeLtDiff = (rangeLtF - rangeLtR);
    wallAng = wallAngle(rangeLtDiff);
  }
}

//------------------------------------------------
void frontSideRange () {
//  Uses the front side sonars to find the distance to right and left hallway walls
//  ranges rounded to nearest cm
  delay(20);
  pinMode(RtF_TrigEchoPin, OUTPUT);
  pulseOut(RtF_TrigEchoPin, TrigPulse);
  pinMode(RtF_TrigEchoPin, INPUT);
  rangeRtF = pulseIn (RtF_TrigEchoPin, HIGH)/58.0;
  
  delay(20);    
  pinMode(LtF_TrigEchoPin, OUTPUT);
  pulseOut(LtF_TrigEchoPin, TrigPulse);
  pinMode(LtF_TrigEchoPin, INPUT);
  rangeLtF = pulseIn (LtF_TrigEchoPin, HIGH)/58.0;

  hallWidth = rangeRtF + rangeLtF + roboWidth;     
}

//--------------------------------------------
void rearSideRange () {
//  Uses the rear side sonars to find the distance to right and left hallway walls
//  ranges rounded to nearest cm

  delay(20);
  pinMode(RtF_TrigEchoPin, OUTPUT);
  pulseOut(RtR_TrigEchoPin, TrigPulse);
  pinMode(RtF_TrigEchoPin, INPUT);
  rangeRtR = pulseIn (RtR_TrigEchoPin, HIGH)/58.0;
  
  delay(20);
  pinMode(LtF_TrigEchoPin, OUTPUT);
  pulseOut(LtR_TrigEchoPin, TrigPulse);
  pinMode(LtF_TrigEchoPin, INPUT);
  rangeLtR = pulseIn (LtR_TrigEchoPin, HIGH)/58.0;      
}

//----------------------------------------
//----------------------------------------
void CrossHallRange()  {
    HallRangeLt();
    HallRangeRt();
 
    endHallWidth = rangeRtHall + rangeLtHall + roboWidth;    
}

//--------------------------------------------------
void HallRangeLt() {
    delay(30);
    pinMode(LtHall_pin, OUTPUT);
    pulseOut(LtHall_pin, TrigPulse);
    pinMode(LtHall_pin, INPUT);
    rangeLtHall = pulseIn(LtHall_pin, HIGH)/58.0;
}


//--------------------------------------------------
void HallRangeRt()  {
    delay(30);
    pinMode(RtHall_pin, OUTPUT);
    pulseOut(RtHall_pin, TrigPulse);
    pinMode(RtHall_pin, INPUT);    
    rangeRtHall = pulseIn(RtHall_pin, HIGH)/58.0; 
}

//----------------------------------------------------
float wallAngle (float rangeDiff) { 
  float angle;
  float angleFlag;
  float baseline = 19.4;   // distance between front and rear sonars (cm)

  angleFlag = false;
  if (abs(rangeDiff) >= baseline) {
    angle = 0.0;
    angleFlag = true;
  }
  else {
    angle = 57.296*asin(rangeDiff/baseline);    
  }
  return angle;
}

//---------------------------------------------------
float Lidar() {
float sum;
float dist;
  
  digitalWrite(9, LOW);
  sum = 0;
   for (int i = 0; i < 100; i++) {
    dist = pulseIn(8, HIGH)/10;
    sum += dist;
   }
   digitalWrite(9, HIGH);
   dist = sum/100;
   return dist;
 }
 
//-------------------------------------------------
void pulseOut(int pin, int duration) {
  delayMicroseconds(12);
  pinMode(pin, OUTPUT);  
  digitalWrite(pin, LOW);
  delayMicroseconds(12);
  digitalWrite(pin, HIGH);
  delayMicroseconds(duration);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
  delayMicroseconds(12);
}
