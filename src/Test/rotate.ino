void rotateAbsolute(double setpoint) { /* Rotates an absolute value provided 
  const float Kp = 1;
  const float Kd = 0.01;
  
  static double delError = 0;
  static double error = 0;
  double angle = gyro.angleDeg();
  
  float newError = setpoint - angle;
  delError = newError - error;
  error = newError;
  
  float corr = -(Kp*error + Kd*delError);
  
  // normalize corr value between 1 & -1
  
  Serial.println("Corrective Value =" + String(corr));
}

void rotateRelative() { /* Rotates to a given angle based on current angle provided by gyro

}
