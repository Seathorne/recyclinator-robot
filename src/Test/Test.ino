#include "Drive.h"
#include "Sonar.h"

// MD49 motor controller
Drive drive(Serial2);

// Sonar distance sensors
Sonar sonar_front_left(27);
Sonar sonar_front_right(28);
Sonar sonar_back_left(26);
Sonar sonar_back_right(29);
Sonar sonar_hall_left(24);
Sonar sonar_hall_right(25);

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(1000);

  if (!IsAutoMode()) return;

  UpdateDrive();
  
  UpdateSonar();
  PrintSonar();
}

bool IsAutoMode() {
  const int BUSY_PIN = 33;
  return digitalRead(BUSY_PIN) == 0;
}

void UpdateDrive() {
  drive.Update();
}

void UpdateSonar() {
  sonar_front_left.Update();
  sonar_front_right.Update();
  sonar_back_left.Update();
  sonar_back_right.Update();
  sonar_hall_left.Update();
  sonar_hall_right.Update();
}

void PrintSonar() {
  Serial.print("--- Sonar Ranges ---\n");
  Serial.print(" FrL=");
  Serial.print(sonar_front_left.Range());
  Serial.print("\n FrR=");
  Serial.print(sonar_front_right.Range());
  Serial.print("\n BkL=");
  Serial.print(sonar_back_left.Range());
  Serial.print("\n BkR=");
  Serial.print(sonar_back_right.Range());
  Serial.print("\n HaL=");
  Serial.print(sonar_hall_left.Range());
  Serial.print("\n HaR=");
  Serial.print(sonar_hall_right.Range());
  Serial.print("\n--------------------\n\n");
}
