//                    WALLFOLLOW
//                   24 November 2021

boolean ReceiveEnc = false;
boolean printFlag = false;

byte SynchByte = 0x0000;
byte MtrStop = 128;
byte MtrSlow = 210;    //example motor speeds
byte MtrMed  = 238;
byte MtrFast = 245;
byte leftSpeed;
byte rightSpeed;
byte speedMaxDiff;

int rc_active = 33;            //Signal from NanoEvery indicating R/C Control when high
int busy = 0;
int RightFrontSonar_pin = 28;  //sonar #4

float rangeRight;
float setPoint;
float standOff;
float error;
float errorOld;
float delError;
float Kp;
float Kd;

unsigned long T0;
unsigned long T;

void setup() {
  SetPinModes();
  InitializeSerialPorts();
  
  leftSpeed  = MtrSlow;
  rightSpeed = MtrSlow;
  MtrSpeed(MtrStop, MtrStop);
  
  setPoint = 60.0;                 //follow distance from wall (cm)
  Ping();
  standOff = rangeRight;
  error = setPoint - standOff;
  errorOld = error;  
  speedMaxDiff = 10;

  printFlag = false;  
  Kp = 0.1;
  Kd = 0.0;  

  T0 = millis();
}

void loop() { 
   T = millis();      
   if(T >= T0 + 131 ) {  
     T0 = millis();
     Follow();
   }

  if(printFlag == true) {
    Report();
    printFlag = false;
  }    
}
