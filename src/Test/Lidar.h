/*
#ifndef Lidar
#define Lidar

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
//////////////////carryover////////////////////
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
//////////////////////////////////////////////

//lidar class////////////////////////////////
class Lidar : public LIDARLite
{
  public:
  float LidarPoint(float servoAng);
  float lidardistance();
  private:
  int pin;
  int Point(float ang);
}
////////////////////////////////////////////
#endif
*/
