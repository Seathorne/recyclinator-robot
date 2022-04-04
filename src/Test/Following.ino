void Follow(float distance, float driveSpeed, Sonar &sonar) {
  const float Kp = 1;
  const float Kd = 0.01;
  const float maxSpeedDiffPercent = 0.10;

  static float error = 0;
  static float delError = 0;
  
  float range = sonar.Range();
  
  float newError = distance - range;
  delError = newError - error;
  error = newError;

  // float corr = Kp*error + Kd*delError;
  // Serial.println("Following| orig corr = " + String(corr));

  // Scale corrective factor
  float corr = abs(distance / range);
  Serial.println("Following| scaled corr = " + String(corr));

  // Clamp corrective factor
  corr = min(max(corr, 1 - maxSpeedDiffPercent), 1 + maxSpeedDiffPercent);
  Serial.println("Following| clamped corr = " + String(corr));

  float speedL = driveSpeed * corr;
  float speedR = driveSpeed;
  
  Serial.println("Following| leftSpeed = " + String(speedL));
  Serial.println("Following| rightSpeed = " + String(speedR));
  drive.SetSpeed(min(max(speedL, -1), 1), min(max(speedR, -1), 1));
}

void FollowLR(float leftRight, float minRange, float rightSpeed, Sonar &left, Sonar &right)
{
  float width = left.Range() + right.Range();
  float setpointL = leftRight * width;

  Follow(max(setpointL, minRange), rightSpeed, left);
}

void OldFollow(float rangeSetpoint, float driveSpeed, Sonar &sonar)
{
  const float Kp = 0.2;
  const float Kd = 5;
  const float speedMaxDiff = 10 / 128.0;
  
  static float prevError = 0;

  float range = sonar.Range();
  float error = rangeSetpoint - range;
  float delError = (error - prevError);
  prevError = error;

  float corr = -(Kp*error + Kd*delError);
  Serial.println("Following| corr=" + String(corr));
  if (corr > 1)
    corr = 1;
  else if (corr < -1)
    corr = -1;
  
  float corrLim = corr*speedMaxDiff;
  float leftSpeed = driveSpeed + corrLim;
  float rightSpeed = driveSpeed;
  drive.SetSpeed(leftSpeed, rightSpeed);
}
