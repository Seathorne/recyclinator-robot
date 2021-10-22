       

/*********************************************************
                         ARDUINO
                        RECYLINATOR II
                        Milestone 1 - Hallway Transitions
                        EMG40 & MD49
                       18 February 2018

**********************************************************/

#include <Servo.h>
Servo LidarServo;               //Left write(129);  Forward write(87);  Right write(45)

#define SynchByte 0x00           // Command byte
#define  North     1             // values for hall follow direction
#define  East      2
#define  South     3
#define  West      4
#define  Left      0        // values for wall follow side
#define  Right     1
#define  Straight  2
#define  faceLeft    129    // values for Lidar servo position
#define  faceForward 87
#define  faceRight   45

const float pi = 3.14159;
const float radToDeg = 57.2958;
const float roboWidth = 35;        //distance (cm) between right and left side sonars (outer transducer edges)

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
byte LtR_TrigEchoPin = 26;
byte LtF_TrigEchoPin = 27;
byte RtF_TrigEchoPin = 28;
byte RtR_TrigEchoPin = 29;
byte LtHall_pin = 24;
byte RtHall_pin = 25;
byte LidarMonitor_pin = 8;
byte LidarTrigger_pin = 9;
byte LidarPwrEn_pin = 10;
byte MtrBack = 82;
byte MtrStop = 128;
byte MtrTurn = 200;
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
byte hallEndType;

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
float lidarDist;

long enc;
long encoderLt;
long encoderRt;
long hall45AdvEnc;
long hallAdvCenterEnc;
long hallCheckEnc;         
long hallEndEnc;             // encoder value before reaching feature to ck for hall end 
long hallLengthEnc;          // encoder value between hall shortest straight walls 
long hallEnd;
long timeTemp;
unsigned long EncWait;

String hallCase;

void setup()  {
  delay(500);
  hallID= 2;
  hallDir = North;
  iTurn = 0;
  wallDistVal = 80;
  
  In_Hallway = true;
  At_Turn_Node = false;
  FirstHallFlag = true;
  ncount = 0;

  SetPinModes();  
  InitializeSerialPorts();
  ConfigMotors();  

  LidarServo.write(faceForward);

  SetAcceleration(3);   
  LtMtrSpeed = MtrMed;
  RtMtrSpeed = MtrMed;  
  Kp = 0.5;
  Ka = 0.75;
  
  digitalWrite(LidarPwrEn_pin, HIGH);  
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
  
    else {                      //if RC STOP engaged, stop "slowly" i.e. accel value = 3
      SetAcceleration(3);
      MtrSpeed(MtrStop, MtrStop);
      Serial1.println("  idle  ");
//      PrintMon();
      timeTemp = millis();
      EncRst();
    }
 }
 
 


