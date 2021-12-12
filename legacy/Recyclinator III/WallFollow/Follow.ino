
void Follow() { 
float corr;
float corrLim;  

    Ping();
    error    = setPoint - rangeRight;
    delError = (error - errorOld);
    errorOld = error;   

    corr =  -(Kp*error + Kd*delError);
    
    if (corr > 1)
      corr = 1;
    else if (corr < -1)
      corr = -1;
  
    corrLim = corr*speedMaxDiff;
    leftSpeed = rightSpeed  + corrLim;
  
    MtrSpeed(leftSpeed, rightSpeed);   
    
    printFlag = true;
}
