#include "Pixy.h"

Pixy::Pixy()
    : panLoop(400, 0, 400, true),
      tiltLoop(500, 0, 500, true) {
}

void Pixy::init() {
  pixy.init();
  pixy.setServos(PIXY_RCS_CENTER_POS, PIXY_RCS_CENTER_POS);

  // Use color connected components program for the pan tilt to track 
  pixy.changeProg("color_connected_components");
}

void Pixy::update() {
  if (_shouldDetect == false) {
    return;
  }

  static int i = 0;
  int j;
  char buf[64]; 
  int32_t panOffset, tiltOffset;
  
  // get active blocks from Pixy
  pixy.ccc.getBlocks();
  _detectedAngle = pixy.ccc.blocks[0].m_x;

  // print x and y pos values with respect to the center of the block
  Serial.print("The objects x pos is: ");
  Serial.println(pixy.ccc.blocks[0].m_x);
  Serial.print("The objects y pos is: ");
  Serial.println(pixy.ccc.blocks[0].m_y);
  
  if (pixy.ccc.numBlocks)
  {        
    i++;
    
    if (i%60==0)
      Serial.println(i);
    
    // calculate pan and tilt "errors" with respect to first object (blocks[0]), 
    // which is the biggest object (they are sorted by size).  
    panOffset = (int32_t)pixy.frameWidth/2 - (int32_t)pixy.ccc.blocks[0].m_x;
    tiltOffset = (int32_t)pixy.ccc.blocks[0].m_y - (int32_t)pixy.frameHeight/2;  
  
    // update loops
    panLoop.update(panOffset);
    tiltLoop.update(tiltOffset);
  
    // set pan and tilt servos  
    pixy.setServos(panLoop.m_command, tiltLoop.m_command);
  }  
  else // no object detected, go into reset state
  {
    panLoop.reset();
    tiltLoop.reset();
    pixy.setServos(panLoop.m_command, tiltLoop.m_command);
  }
}

void Pixy::setDetecting(bool shouldDetect) {
  _shouldDetect = shouldDetect;
}

bool Pixy::isDetecting() const {
  return _shouldDetect;
}

bool Pixy::isBinDetected() const {
  return (pixy.ccc.numBlocks > 0);
}

double Pixy::detectedAngle() const {
  return _detectedAngle;
}