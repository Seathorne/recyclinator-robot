       

/*********************************************************
                         ARDUINO
                        RECYLINATOR II
                        Milestone 1
                        EMG40 & MD49
                       4 February 2018

**********************************************************/

#define SynchByte 0x00           // Command byte
#define  North     1          // Define directions
#define  East      2
#define  South     3
#define  West      4
#define  Left      0
#define  Right     1
#define  Straight  2

const float pi = 3.14159;
const float radToDeg = 57.2958;
const float roboWidth = 35;        //distance between right and left side sonars

boolean At_Turn_Node;
boolean In_Hallway;
boolean FirstHallFlag;
boolean At_Fail;
boolean ID;
boolean termination;
boolean ReceiveEnc = false;

byte caseNum;
byte SetMode = 0x34;
byte TrigPulse = 10;
byte LtR_TrigEchoPin = 50;
byte LtF_TrigEchoPin = 51;
byte RtF_TrigEchoPin = 52;
byte RtR_TrigEchoPin = 53;
byte LtHall_pin = 48;
byte RtHall_pin = 49;
byte MtrBack = 82;
byte MtrStop = 128;
byte MtrTurn = 160;
byte MtrSlow = 210;
byte MtrMed = 238;
byte MtrFast = 245;

byte LtMtrSpeed;
byte RtMtrSpeed;
byte LtMtrSpd;
byte RtMtrSpd;
byte Corr;

byte hallID;
byte turnDir;
byte hallDir;
byte turnHall9East[] = {2, 0, 0, 0, 1, 2, 1, 1, 1, 0, 0, 1, 1, 1, 2, 1, 0, 0, 0, 2, 3};
byte turnHall2North[] = {0, 0, 0, 0, 3};
byte angDir;
byte Dir;
byte EncIndex = 0;

byte rc_active = 33;                          //Signal from BX-24 indicating R/C Control when high
byte busy;
byte ncount;
byte featureList[20];
byte featureIndex;
byte iTurn;

int angLimit;
int angTurn;
int gyroAngle;
int turnAng;

float angDel;
float endHallWidth;
float featureDepth;
float HW;
float Ka;
float Kp;
float rangeLtHall;
float rangeRtHall;
float hallWidth;
float rangeRtF;
float rangeLtF;
float rangeRtR;
float rangeLtR;
float wallAng;
float wallDel;
float wallDistVal;

long enc;
long encoderLt;
long encoderRt;
long hall45AdvEnc;
long hallAdvCenterEnc;
long hallEndEnc;
long hallLengthEnc;
long timeTemp;
unsigned long EncWait;

String hallCase;

void setup()  {
  delay(500);
  hallID= 2;
  hallDir = North;
  Dir = Right;
  iTurn = 0;
  wallDistVal = 80;
  
  In_Hallway = true;
   At_Turn_Node = false;
  FirstHallFlag = false;
  busy = 1;
  ncount = 0;

  LtMtrSpeed = MtrMed;
  RtMtrSpeed = MtrMed;  
  Kp = 0.5;
  Ka = 0.75;
  
  SetPinModes();  
  InitializeSerialPorts();
  ConfigMotors();
  Stats();
}

void loop()  {
    busy = digitalRead(rc_active);          //busy = 0 when in Auto Mode
    if(busy == 0) { 
      if (In_Hallway) 
        HallwayNavigation();
      if (At_Turn_Node) {
        Serial1.println(" at Turn Node ");   
        ChangeHall();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
      }      
  }      
  
    else {                      //if RC STOP engaged, stop "slowly" i.e. accel value = 4
      Serial.println("else");
      MtrSpeed(MtrStop, MtrStop);
      Serial1.println("  idle  ");
      Serial1.write(9);
//      PrintMon();
      timeTemp = millis();
//      Serial3.write('Z');
//      delay(50);
//      while (Serial3.read() >= 0);    // clear gyro buffer  
      EncRst();
    }
 }
 
 


