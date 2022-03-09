forwardmovement(float speed, float angle)
{
  float Speed=speed;
  float dist=55;
  float currentAng=angleDeg();
  const float Kp = .25;
  const float Kd = 0.01;  
  
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
  delerror=newError-error;
  error=newError;
  
  
  float corr = -(Kp*error+Kd*delError);
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
