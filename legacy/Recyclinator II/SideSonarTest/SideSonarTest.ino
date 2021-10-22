
byte rc_active = 33;           //Signal from BX-24 indicating R/C Control when high
byte trigPulse = 10;
byte busy = 0;
byte LtF_TrigEchopin = 51;
byte RtF_TrigEchopin = 52;
byte LtR_TrigEchopin = 50;
byte RtR_TrigEchopin = 53;

float rangeLtF;
float rangeRtF;
float rangeLtR;
float rangeRtR;

//--------------------------------------------------
void setup()  {
  delay(1000);
  InitialiseSerialPorts();
  SetPinModes();                       
}

void loop()  {
  busy = digitalRead(rc_active);          //busy = 0 when in Auto Mode
  if (busy == 0) {
    Ranger();
     Print();
    PrintMon();
  }

  else {
    Serial1.println("  idle  ");
    Serial1.write(9);
    delay(100);
  }
}
