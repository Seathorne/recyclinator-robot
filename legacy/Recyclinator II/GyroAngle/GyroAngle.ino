/*
     L3G4200D 3-axis Gyro Set-up for 250 deg/sec max rate
     Interfaces with Mega Recyclinator code
                    2 February 2018      
 */
#include <Wire.h>

// Gyro Registers
#define CTRL_REG1 0x20  // data rate, bandwidth, pwr mode, axes enable
#define CTRL_REG2 0x21  // high pass filter cutoff
#define CTRL_REG3 0x22  // interrupts
#define CTRL_REG4 0x23  // update mode, LSB/MSB, full scale, serial mode
#define CTRL_REG5 0x24  // FIFO en, high pass en

const float SC250 = 0.00875; 
const float SC500 = 0.0175; 
const float SC2000 = 0.070;

 char val = 'G'; 

byte num;
byte resultMSB; 
byte resultLSB; 
byte SynchByte = 0x00; 
byte SetMode = 0x34; 

int L3G4200D_Address = 105;   //I2C address of the L3G4200D
int Rth; 
float SC; 
int z; 
int zero;
int zRate;
unsigned int result;
 
float delTime;

float angle; 
float rate; 
 
long sum; 
long time; 
long time0;

void setup() {
  Wire.begin();   
  Serial.begin(19200);     //pin 0 requests from Mega; pin 1 TX out to Mega 2650

  setupL3G4200D(250);     // Configure L3G4200  - 250, 500 or 2000 deg/sec
  delay(1500);            //wait for the sensor to be ready 
 
  sum = 0.0; 
  for(int i = 0; i < 100; i++) {
    z = getGyroValues();
    sum =  sum + z;
  }
  zero = sum/100; 
  angle = 0.0;  
  time0 = millis();  
}

void loop() {
//  gets Gyro values and integrates to find angle  
calc: ;  
  zRate = getGyroValues();        // This will update x, y, and z with new values
  rate = SC*float(zRate - zero);    
  delTime = (millis() - time0);
  time0 = millis();    
  angle = angle + delTime*rate/1000;

//  Waits for Mega command to either zero gyro or get current angle 
  if(Serial.available()) {  
    val = Serial.read();    
    if (val == 'Z'){
      angle = 0.0;
      goto calc;
      }
    else if (val == 'G') {
      if (angle > 0.0)
        result = floor(angle + 0.5);
      else
        result = ceil(angle - 0.5);
      
      resultMSB = highByte(result);
      resultLSB = lowByte(result);

      Serial.write(resultMSB);
      Serial.write(resultLSB); 
     goto calc;
    }
  }   
}

