#ifndef GYRO_H
#define GYRO_H

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

class Gyro
{
  public:
    Gyro(int pin);

    void init();
    void update();

    /* Returns the theta angle of the IMU,
        in degrees (-180..180]. */
    float angleDeg() const;

  private:
    int _pin;
    double _angleDeg;
    Adafruit_BNO055 sensor;
    sensors_event_t sensorEvent;
};

#endif // GYRO_H
