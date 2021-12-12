    

/*********************************************************
                         ARDUINO
              Recyclinator III Motor & Encoder Test
                      19 November 2021

 Drives motors in auto mode with example motor speeds
 Retrieves encoder values      
 Prints time (ms), commanded motor speeds, wheel encoder values to Logomatic                  
**********************************************************/

boolean ReceiveEnc = false;

byte SynchByte = 0x0000;
byte MtrStop = 128;
byte MtrSlow = 210;    //example motor speeds
byte MtrMed  = 238;
byte MtrFast = 245;
byte LtSpd;
byte RtSpd;
byte EncIndex = 0;

int rc_active = 33;            //Signal from NanoEvery indicating R/C Control when high
int busy = 0;

long encoderLt;
long encoderRt;
long T0;

void setup()  {
  delay(500);
  SetPinModes();  
  InitializeSerialPorts();;
  LtSpd = MtrSlow;           //sample speed for testing Auto
  RtSpd = MtrSlow; 

  T0 = millis();
  EncRst();
}

void loop()  {
    busy = digitalRead(rc_active);       //busy = 0 when in Auto Mode

    if(busy == 0) {
      MtrSpeed(LtSpd, RtSpd);
      Encoders();  
      Print();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
      }          

    else {                        //if RC STOP engaged, stop "slowly" i.e. accel value = 4
      T0 = millis();
    }
 }
 
 
