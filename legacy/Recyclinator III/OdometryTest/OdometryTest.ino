 /*                       ODOMETRY TEST
 *                      20 november 2021
 *  
 *  The program runs the robot straight for a given distance and 
 *  finds the robot pose (x, y, theta) using odometry based on
 *  motor encoder counts and IMU angles.  
*/  

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);

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
int leftDelta;
int rightDelta;
int lastLeft;
int lastRight;

float pi = 3.1415926535;
float DegTRad = pi/180;
float x;
float y;
float U;
float theta;

long encoderLt;
long encoderRt;

unsigned long T0;
unsigned long T;

void setup() {

// Initialize the IMU
if(!bno.begin())  {
      //There was a problem detecting the BNO055 .. check connections
      Serial.print("Ooops, no BNO055 detected ..  Check wiring or I2C address");
      while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true); 

  SetPinModes();  
  InitializeSerialPorts();
  InitializeVariables();

//initialize motor speeds to equal values;
  LtSpd = MtrSlow;           //sample speed for testing Auto
  RtSpd = MtrSlow; 
  EncRst();
  T0 = millis();  
}
  
void loop() {
  MtrSpeed(LtSpd, RtSpd);  
  busy = digitalRead(rc_active); 
  if(busy == 0) {      //busy = 0 when in Auto Mode
// run for 400 cm    
    while(U < 400) { 
      T = millis();
// sample encoders every 100 ms      
      if(T >= T0 + 100) {
        T0 = millis();
        Encoders();
        Odometry(encoderLt,encoderRt);     
// adjust left motor to equalize motor speeds         
        if(leftDelta > rightDelta)
          LtSpd = LtSpd - 1;
        else if (leftDelta < rightDelta)
          LtSpd = LtSpd + 1;           
          
        MtrSpeed(LtSpd, RtSpd);
        Print();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
      }     
    }
    MtrSpeed(MtrStop, MtrStop);
 //prevent loop from continuing and dump logomatic buffer
    while(1) {                  
      Serial1.println("idle");
      delay(100);
    }    
  }
}  
