
float SonarRange(int sonar_pin) {
float echo;  
float range;
  pulseOut(sonar_pin);                      //sends out a ultrasonic pulse
  pinMode(sonar_pin, INPUT);
  echo = pulseIn (sonar_pin, HIGH);         //times the return pulse
  range = echo/58.0;                        //converts round trip pulse time to distance
  delay(50);  
  return range;
}

//pings the ultrasonic sensor
void pulseOut(int pin) {
  pinMode(pin, OUTPUT);  
  digitalWrite(pin, HIGH);
  delayMicroseconds(12);
  digitalWrite(pin, LOW);
}

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
