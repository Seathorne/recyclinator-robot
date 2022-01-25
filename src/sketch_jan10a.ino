#include "lidar.h"
void interruptthis();
Lidar lidar;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  lidar.Start();
  attachInterrupt(digitalPinToInterrupt(lidar.Encode), interruptthis, CHANGE); //setting up encoder
  Serial.println("made it to calibration");
  lidar.HandleCalibration();
  Serial.println("I made it past calibration");
  lidar.MoveTo(400);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
void interruptthis(){
  
  lidar.UpdateEncoder();
}
