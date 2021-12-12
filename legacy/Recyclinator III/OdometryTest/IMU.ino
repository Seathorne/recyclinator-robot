float IMU() {
// returns the pose angle theta in degrees
float currentAngle;  
float poseAngle;

// Get a new IMU sensor event 
  sensors_event_t event;
  bno.getEvent(&event);   
  currentAngle = event.orientation.x;

// IMU measures the angle CW from 0 - 360 deg
// Odometry angles measured positive CCW from zero to 180 
//  and negative CW zero to 180

  if((currentAngle > 0) && (currentAngle <= 180)) {
    poseAngle = - currentAngle;
  }
  
  else if((currentAngle > 180) && (currentAngle <= 360)) {
    poseAngle = 360 - currentAngle; 
  }

  return poseAngle;
}
