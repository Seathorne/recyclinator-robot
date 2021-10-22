
#define cmdByte 0x00           // Command byte
byte SynchByte = 0x00;
byte SetMode = 0x34;
byte MtrMed = 238;
byte MtrStop = 128;
byte LtSpeed;
byte RtSpeed;

byte rc_active = 33;           //Signal from BX-24 indicating R/C Control when high
byte trigPulse = 10;
byte busy = 0;
byte LtF_TrigEchopin = 51;
byte RtF_TrigEchopin = 52;
byte LtR_TrigEchopin = 50;
byte RtR_TrigEchopin = 53;
byte LtHall_TrigEchopin = 48;
byte RtHall_TrigEchopin = 49;

float rangeLtF;
float rangeRtF;
float rangeLtR;
float rangeRtR;
float rangeLtHall;
float rangeRtHall;
//--------------------------------------------------
void setup()  {
  delay(1000);
  InitialiseSerialPorts();
  SetPinModes();      
  ConfigMotors(); 
  MtrSpeed(MtrStop, MtrStop);
}

void loop()  {
  busy = digitalRead(rc_active);          //busy = 0 when in Auto Mode
  if (busy == 0) {
    Ranger();
//    MtrSpeed(MtrMed, MtrMed);    
//    Print();
    PrintMon();
  }

  else {
    Serial1.println("  idle  ");
    Serial1.write(9);
    delay(100);
  }
}
