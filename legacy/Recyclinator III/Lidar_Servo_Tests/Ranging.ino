
float LidarPoint() {
float angle;
float D;
  
  if (go == 1) {
// point the lidar    
    pulselen = Point(servoAng);  
    pwm.setPWM(servonum, 0, pulselen);
    delay(1000);                 // time for servo to reach position
                                 //  before taking a lidar distance measurement

// Find the avg distance 
    D = myLidarLite.distance(false);    
    Serial.print(servoAng,0);
    Serial.write(9);
    Serial.println(D,1);     
   }

  go = 0;  
}

int Point(float ang) {
int pulsePWM = 0;
  if(ang < 0)   ang = 0.0;
  if(ang > 180) ang = 180.0;

  pulsePWM = int(SERVOMIN + (ang/180)*(SERVOMAX - SERVOMIN));

  return pulsePWM;
}
