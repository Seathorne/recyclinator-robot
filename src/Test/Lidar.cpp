#include "Lidar.h"
//////////////////////carryover from the other file///////////////////
#include <Wire.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
/////////////////////////////////////////////////////////////////////

//////////lidar class///////////////////////////////////////////////
class Lidar{
  public:
  Lidar(int p)
  {
    pin=p;
  }
  float LidarPoint(float servoAng) 
{
  int pulselen;
// point the lidar    
    pulselen = Point(servoAng);  
    pwm.setPWM(servonum, 0, pulselen);
    delay(1000);                 // time for servo to reach position
                                 //  before taking a lidar distance measurement                             
}
float lidardistance();
{
    float D;
    D = myLidarLite.distance(false);    
    Serial.print(servoAng,0);
    Serial.write(9);
    Serial.println(D,1);     
    return D;
}
  private:
  int pin;
  int Point(float ang)
{
  int pulsePWM = 0;
  if(ang < 0)   ang = 0.0;
  if(ang > 180) ang = 180.0;

  pulsePWM = int(SERVOMIN + (ang/180)*(SERVOMAX - SERVOMIN));

  return pulsePWM;
}
}
///////////////////////////////////////////////////////////////////////
