void Odometry(long left, long right) {

float delX;
float delY;
float delU; 
float delUleft;
float delUright;
float delTheta;
float current_angle;
float CmStar = 4.071247623e-02;  // cm traveled/encoder count
  
  leftDelta  = (left - lastLeft);
  rightDelta = (right - lastRight);
  lastLeft  = left;
  lastRight = right; 

  delUleft  = CmStar*leftDelta;
  delUright = CmStar*rightDelta;      
  delU = (delUleft + delUright)/2;

// Get a new IMU sensor event 
  theta = IMU()*DegTRad;

  delX = delU*cos(theta);
  delY = delU*sin(theta);
  x += delX;
  y += delY;
  U += delU; 
}
