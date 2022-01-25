#ifndef SONAR
#define SONAR
#include <Arduino.h>
class Sonar {
  public:
    Sonar(int pin);
    
    float Range() const;

    void Update();
  
  private:
    int _pin;
    float _range;

    void GetRange();
};

#endif
