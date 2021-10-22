    

/*********************************************************
                         ARDUINO
              Recyclinator III Motor Test
                      12 October 2021

!!!!!  Motor Commands Should Only Be Made in Busy == 0 loop  !!!!!
**********************************************************/

boolean ReceiveEnc = false;

byte SynchByte = 0x0000;
byte MtrStop = 128;
byte MtrSlow = 210;
byte MtrMed  = 238;
byte MtrFast = 245;
byte LtSpd;
byte RtSpd;
byte EncIndex;


int rc_active = 33;                          //Signal from BX-24 indicating R/C Control when high
int busy = 0;

long encoderLt;
long encoderRt;
long T0;
unsigned long EncWait;

void setup()  {
  delay(500);
  SetPinModes();  
  InitializeSerialPorts();
  LtSpd = MtrSlow;
  RtSpd = MtrSlow;

  T0 = millis();
}

void loop()  {
    busy = digitalRead(rc_active);       //busy = 0 when in Auto Mode

    if(busy == 0) {
      MtrSpeed(LtSpd, RtSpd);      
//      if((ReceiveEnc == true) && (millis() > EncWait)) Encoders;      
      Encoders(encoderLt, encoderRt);  
      PrintAuto();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
      }          

   else {
    T0 = millis();
    }
 }
 
 
