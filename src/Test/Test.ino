#include "Drive.h"
#include "Gyro.h"
#include "Robot.h"
#include "Sonar.h"

// MD49 motor controller
Drive drive(Serial2);
Gyro gyro(55);
float angleMaint;

// Sonar distance sensors
Sonar sonar_front_left(27);
Sonar sonar_front_right(28);
Sonar sonar_back_left(26);
Sonar sonar_back_right(29);
Sonar sonar_hall_left(24);
Sonar sonar_hall_right(25);
Sonar sonar_front(34);

Robot robot(drive, gyro);

enum AutoRoutine
{
  DoNothing,
  Drive,
  Rotate,
  WallFollow,
  StopEndOfHallway,
  RotateDrive,
  TestMinSpeed,
};

AutoRoutine autoRoutine = AutoRoutine::DoNothing;
int autoStep = 0;

void setup() {
  Serial.begin(9600);

  /* Initialize subsystems */
  robot.init();

  angleMaint=gyro.angleDeg();
  Serial.println("Robot| setup complete.");
}

void loop() {
  constexpr long FrameLength = 1000;
  constexpr bool PrintAll = true;

  static long prevTime = millis();
  static bool prevIsAutoMode;

  /* Only loop within specfied frequency
      and in autonomous mode */
  long currTime = millis();
  bool isAutoMode = IsAutoMode();
  if (currTime - prevTime < FrameLength || !isAutoMode )
    return;
  prevTime = currTime;
  prevIsAutoMode = isAutoMode;

  /* Update sensors & subsystems */
  robot.update();
  UpdateSonar();

  /* Perform autonomous routine step */
  switch (autoRoutine) {

    case TestMinSpeed: {
        drive.SetSpeed(0.25, -0.25);
    }; break;

    case Drive: {
      if (autoStep == 0)
      {
        robot.startDrive(2,.7);
        autoStep++;
      }
      else if (robot.mode() == Mode::Driving)
      {
        robot.step();
      }
      else
      {
        autoRoutine = AutoRoutine::DoNothing;
      }
    }; break;

    case Rotate: {
      if (autoStep == 0)
      {
        robot.startRotate(60);
        autoStep++;
      }
      else if (robot.mode() == Mode::Rotating)
      {
        robot.step();
      }
      else
      {
        autoRoutine = AutoRoutine::DoNothing;
      }
    }; break;

    // Follow wall at range=60cm, speed=75%
    case WallFollow: {
      robot.
      // Follow(60, 0.75, sonar_front_left);
      // FollowLR(0.50, 40, 0.75, sonar_front_left, sonar_front_right);
      OldFollow(60, 0.75, sonar_front_right);
      robot.
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
	  
    case RotateDrive: {
      switch (autoStep) {
        case 0:
          Serial.println("Rotate| starting rotation");
          robot.startRotate(45);
          autoStep++;
          break;
        case 1:
          if (robot.mode() == Mode::Stopped) {
            Serial.println("Rotate| rotation complete");
            autoStep++;
          } else {
            robot.step();
          }
          break;
        case 2:
          Serial.println("Drive| starting drive");
          robot.startDrive(2.5, 0.7);
          autoStep++;
        case 3:
          if (robot.mode() == Mode::Stopped) {
            Serial.println("Drive| drive complete");
            autoStep++;
          } else {
            robot.step();
          }
          break;
        case 4:
          Serial.println("Rotate| starting rotation");
          robot.startRotate(45);
          autoStep++;
          break;
        case 5:
          if (robot.mode() == Mode::Stopped) {
            Serial.println("Rotate| rotation complete");
            autoStep++;
          } else {
            robot.step();
          }
          break;
        case 6:
          Serial.println("Drive| starting drive");
          robot.startDrive(1, 0.7);
          autoStep++;
        case 7:
          if (robot.mode() == Mode::Stopped) {
            Serial.println("Drive| drive complete");
            autoStep++;
            autoRoutine = AutoRoutine::DoNothing;
          } else {
            robot.step();
          }
          break;
      }
    }; break;
	
  }

  /* Print info about subsystems */
  if (PrintAll) {
    Print(robot.drive());
    Print(robot.gyro());
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
    return false;
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
