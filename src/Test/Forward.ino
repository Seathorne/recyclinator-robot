/*
#include "gyro.h"
void forwardmovement(float speed, float angle, Gyro &gyro)
{
  float Speed=speed;
  float dist=55;
  float currentAng=gyro.angleDeg();
  const float Kp = 0.25;
  const float Kd = 0.01;  
  float correctedAngle;
  correctedAngle=currentAng-angle;
  
  
  
  if(correctedAngle>180)
  {
    correctedAngle-=360;
  }
  else if(correctedAngle<-180)
  {
    correctedAngle+=360;
  }
  
  static float error = 0;
  static float delError = 0;
  
  float newError = 0-correctedAngle;
  delError=newError-error;
  error=newError;
  Serial.println("Set Angle "+String(angle));
  Serial.println("Current Angle "+String(gyro.angleDeg()));
  float corr = -(Kp*error+Kd*delError);
  Serial.println("Corr value"+String(corr));
  if (corr > .1) {
    corr = .1;
  }
    else if (corr < -.1)
  {
    corr = -.1;
    }


  //on top of that, I guess you have to really ask how we're going to merge the two, as two routines
  //controlling the motor independently is bound to cause some issue.
  float leftSpeed = speed;
  float rightSpeed= speed+corr;
  Serial.println("s");
  Serial.println(leftSpeed);
  drive.SetSpeed(leftSpeed, rightSpeed);
}
*/  //depriciated, kept for posterity.