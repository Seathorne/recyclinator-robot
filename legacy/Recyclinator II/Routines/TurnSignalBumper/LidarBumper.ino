
void LidarBump()  {
  valLidarOne = LidarPulse(lidarOne);    
  valLidarTwo = LidarPulse(lidarTwo);
  valLidarThree = LidarPulse(lidarThree);
  valLidarFour = LidarPulse(lidarFour);
  valLidarFive = LidarPulse(lidarFive);
}

float LidarPulse(byte lidarNum) {
float val;  
  pinMode(lidarNum, OUTPUT);
  digitalWrite(lidarNum, HIGH);
  delayMicroseconds(5);
  pinMode(lidarNum, INPUT);
  val = pulseIn(lidarNum, HIGH)*17.15/1000;
  return val;
}

