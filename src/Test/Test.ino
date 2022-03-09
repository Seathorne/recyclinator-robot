#include "Drive.h"
#include "Gyro.h"
#include "Sonar.h"

// MD49 motor controller
Drive drive(Serial2);
Gyro gyro(55);

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
  StopEndOfHallway,
  Rotate
};

AutoRoutine autoRoutine = AutoRoutine::DoNothing;

void setup() {
  Serial.begin(9600);

  /* Initialize subsystems */
  gyro.init();

  Serial.println("Setup complete.");
}

void loop() {
  constexpr long FrameLength = 1000;
  constexpr bool PrintAll = true;

  static long prevTime = millis();

  /* Only loop within specfied frequency
      and in autonomous mode */
  long currTime = millis();
  if (currTime - prevTime < FrameLength || !IsAutoMode() )
    return;
  prevTime = currTime;

  /* Update sensors & subsystems */
  drive.Update();
  gyro.update();
  UpdateSonar();

  /* Perform autonomous routine step */
  switch (autoRoutine) {
    // Follow wall at range=60cm, speed=75%
    case WallFollow: {
      Follow(0.60, 0.75);
    }; break;

    case StopEndOfHallway: {
      static bool done = false;
      if (!done) {
        drive.SetSpeed(0.6, 0.6);
        
        if (isEndOfHallway(sonar_front_right)) {
          drive.SetSpeed(0.0, 0.0);
          done = true;
        }
      }
    }; break;
    
    case Rotate: {
      rotateAbsolute(60);
    }; break;
  }

  /* Print info about subsystems */
  if (PrintAll) {
    Print(drive);
    Print(gyro);
    PrintSonar();
    Serial.println();
  }
}

bool IsAutoMode() {
  const int BUSY_PIN = 33;
  return digitalRead(BUSY_PIN) == 0;
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

bool isEndOfHallway(Sonar& sonar) {
  constexpr float Threshold = 100;
  static float prevRange;
  static bool firstTime = true;

  float currRange = sonar.Range();

  if (firstTime) {
    firstTime = false;
    prevRange = currRange;
    return;
  }

  bool endOfHallway = (currRange - prevRange) >= Threshold;

  if (endOfHallway) {
    Serial.println("End of hallway, range=" + String(currRange) + ", prevRange=" + String(prevRange));
    Serial.println("  difference=" + String(currRange - prevRange));
  }

  // Update previous range value
  prevRange = currRange;

  return endOfHallway;
}

void PrintSonar() {
  Serial.println("-------- Sonar Ranges --------");
  Serial.println(" Front     = "
    + String(sonar_front.Range()));
  Serial.println(" L/R Front = "
    + String(sonar_front_left.Range()) + "\t"
    + String(sonar_front_right.Range()));
  Serial.println(" L/R Hall  = "
    + String(sonar_hall_left.Range()) + "\t"
    + String(sonar_hall_right.Range()));
  Serial.println(" L/R Back  = "
    + String(sonar_back_left.Range()) + "\t"
    + String(sonar_back_right.Range()));
  Serial.println("------------------------------\n");
}

void Print(Drive& drive) {
  double leftDistance, rightDistance;
  double distance = drive.GetDistance(leftDistance, rightDistance);
  Serial.println("------- Drive -------");
  Serial.println(" Distance = " + String(distance) + "m");
  Serial.println("  Left    = " + String(leftDistance) + "m");
  Serial.println("  Right   = " + String(rightDistance) + "m");
  Serial.println("---------------------\n");
}

void Print(Gyro& gyro) {
  Serial.println("----- Gyroscope -----");
  Serial.println("Angle = " + String(gyro.angleDeg()) + " deg");
  Serial.println("---------------------\n");
}
