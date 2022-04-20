#ifndef PIXY_H
#define PIXY_H

#include <Pixy2.h>
#include <PIDLoop.h>

class Pixy
{
  public:
    Pixy();

    void init();
    void update();

    void setDetecting(bool shouldDetect);

    bool isDetecting() const;
    bool isBinDetected() const;
    
    double detectedAngle() const;

  private:
    Pixy2 pixy;
    PIDLoop panLoop;
    PIDLoop tiltLoop;
    bool _shouldDetect;
    double _detectedAngle;
};

#endif // PIXY_H