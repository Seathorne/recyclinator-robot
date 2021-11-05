void Follow(float distance, float rightSpeed) {
  const float Kp = 1;
  const float Kd = 0.01;

  static float error = 0;
  static float delError = 0;
  
  float rangeRight = sonar_hall_right.Range();
  
  float newError = distance - rangeRight;
  delError = newError - error;
  error = newError;

  float corr = -(Kp*error + Kd*delError);

  if (corr > 1) {
    corr = 1;
  } else if (corr < -1) {
    corr = -1;
  }

  float leftSpeed = rightSpeed + corr; // TODO: this should be capped
  drive.SetSpeed(leftSpeed, rightSpeed);
}
