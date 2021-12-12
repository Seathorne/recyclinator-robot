#include <PIDLoop.h>
#include <Pixy2.h>
#include <Pixy2CCC.h>
#include <Pixy2I2C.h>
#include <Pixy2Line.h>
#include <Pixy2SPI_SS.h>
#include <Pixy2UART.h>
#include <Pixy2Video.h>
#include <TPixy2.h>
#include <ZumoBuzzer.h>
#include <ZumoMotors.h>

#include <Pixy2.h>

Pixy2 pixy;

void setup()
{
  Serial.begin(115200);
  Serial.print("Starting...\n");

  pixy.init();
}

void loop()
{
  pixy.setServos(PIXY_RCS_MIN_POS, PIXY_RCS_MIN_POS);
  pixy.setLED(255, 0, 0); // red
  Serial.print("Setting servo min position");
  delay(1000);

  pixy.setServos(PIXY_RCS_CENTER_POS, PIXY_RCS_CENTER_POS);
  pixy.setLED(0, 255, 0); // green
  Serial.print("Setting servo center position");
  delay(1000);

  pixy.setServos(PIXY_RCS_MAX_POS, PIXY_RCS_MAX_POS);
  pixy.setLED(0, 0, 255); // blue
  Serial.print("Setting servo max position");
  delay(1000);

  pixy.setServos(200, 800);
  Serial.print("Setting servo custom position");
  pixy.setLED(0, 0, 0); // reset led
  delay(1000);  

  pixy.setLamp(1, 1);
  delay(1000);

  pixy.setLamp(0, 0); // reset lamp
  delay(1000);
 
}
