   

/*********************************************************
                           ARDUINO MEGA
                        RECYLINATOR III
                        IMU Sensor Test
                        19 November 2021
            
  Tests the IMU.  Sends the yaw angle to the serial monitor.
  Angle is positive CW from 0 to 360 deg.
  Angle is zero at start-up.
**********************************************************/


#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup() {
  Serial.begin(9600);

// Initialize the IMU
if(!bno.begin())  {
      //There was a problem detecting the BNO055 .. check connections
      Serial.print("Ooops, no BNO055 detected ..  Check wiring or I2C address");
      while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);
  delay(500);  
}

void loop() {
    IMU();
}
