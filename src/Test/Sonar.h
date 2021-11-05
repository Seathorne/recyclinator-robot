#ifndef SONAR
#define SONAR

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

#endif SONAR
