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

    /* Returns the angular velocity of the IMU,
     *   in degrees per second. */
    float angularVel() const;

  private:
    int _pin;
    float _angleDeg;
    float _angularVel;
    Adafruit_BNO055 sensor;
    sensors_event_t sensorEvent;
};

#endif // GYRO_H
