void rotateAbsolute(double setpoint) { /* Rotates an absolute value provided */
  const float Kp = 1;
  const float Kd = 0.01;
  
  static double delError = 0;
  static double error = 0;
  double angle = gyro.angleDeg();
  
  float newError = setpoint - angle;
  delError = newError - error;
  error = newError;
  
  float corr = Kp*error + Kd*delError;
  Serial.println("Rotate| orig corr = " + String(corr));

  // Normalize corrective factor
  corr /= 360.0;

  // Clamp between -1..1
  if (corr > 1) {
    corr = 1;
  } else if (corr < -1) {
    corr = -1;
  }
  
  Serial.println("Rotate| corr = " + String(corr));
  drive.SetSpeed(corr, -corr);
}

void rotateRelative() { /* Rotates to a given angle based on current angle provided by gyro */

}
