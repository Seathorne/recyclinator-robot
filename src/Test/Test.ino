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
Sonar sonar_front(34);

enum AutoRoutine
{
  DoNothing,
  WallFollow,
  TestEncoders
};

AutoRoutine autoRoutine = AutoRoutine::TestEncoders;

void setup() {
  Serial.begin(9600);
}

void loop() {
  constexpr long FrameLength = 1000;
  constexpr bool ShouldPrint = true;

  static long prevTime = millis();

  /* Only loop within specfied frequency
      and in autonomous mode */
  long currTime = millis();
  if (currTime - prevTime < FrameLength || !IsAutoMode() )
    return;
  prevTime = currTime;

  /* Update sensors & subsystems */
  UpdateDrive();
  UpdateSonar();

  /* Perform autonomous routine step */
  switch (autoRoutine) {
    // Follow wall at range=60cm, speed=75%
    case WallFollow: {
      Follow(0.60, 0.75);
    }; break;

    case TestEncoders: {
      double left, right;
      double distance = drive.GetDistance(left, right);
      Serial.print("left distance = " + String(left) + "\n");
      Serial.print("right distance = " + String(right) + "\n");
      Serial.print("average distance = " + String(distance) + "\n");
    }; break;
  }

  /* Print info about subsystems */
  if (ShouldPrint) {
    PrintSonar();
  }
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
  sonar_front.Update();
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
