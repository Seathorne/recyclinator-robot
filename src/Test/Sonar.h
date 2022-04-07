#ifndef SONAR_H
#define SONAR_H

class Sonar {
  public:
    Sonar(int pin);
    
    float Range() const;

    void Init();
    void Update();
  
  private:
    int _pin;
    float _range;

    void GetRange();
};

#endif // SONAR_H
