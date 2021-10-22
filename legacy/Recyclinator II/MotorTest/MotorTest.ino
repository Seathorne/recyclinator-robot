   

/*********************************************************
                         ARDUINO
           Motor Test - Right Motor Hesitation Glitch
                      17 January 2018
                        
**********************************************************/

const float pi = 3.14159;
const float radToDeg = 57.2958;
const float roboWidth = 35;        //distance between right and left side sonars

byte SynchByte = 0x0000;
byte MtrStop = 128;
byte MtrSlow = 210;
byte MtrMed = 238;
byte MtrFast = 245;

byte LtMtrSpeed;
byte RtMtrSpeed;
byte LtMtrSpd;
byte RtMtrSpd;

int rc_active = 33;                          //Signal from BX-24 indicating R/C Control when high
int busy = 0;

long enc;
long encoderLt;
long encoderRt;
long timeTemp;

void setup()  {
  delay(500);
  SetPinModes();  
  InitializeSerialPorts();
  ConfigMotors();
}

void loop()  {
    busy = digitalRead(rc_active);          //busy = 0 when in Auto Mode

    if(busy == 0) {
      MtrSpeed(MtrSlow, MtrSlow);
      GetEncoders();
      enc = encoderLt;
      Print();
//  PrintMon();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
      }          

    else {                      //if RC STOP engaged, stop "slowly" i.e. accel value = 4
      Serial.println("else");
      MtrSpeed(MtrStop, MtrStop);
      Serial1.println("  idle  ");
      Serial1.write(9);
      timeTemp = millis();
      EncRst();
    }
 }
 
 


