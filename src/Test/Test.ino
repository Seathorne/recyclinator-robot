#include "Robot.h"

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

Robot robot;
AutoRoutine autoRoutine = AutoRoutine::DoNothing;

void setup() {
  Serial.begin(9600);

  /* Initialize subsystems */
  robot.init();

  Serial.println("Robot| setup complete.");
}

void loop() {
  constexpr long FrameLength = 200;
  constexpr bool PrintAll = true;

  static long prevTime = millis();
  static bool prevIsAutoMode;
  static int autoStep = 0;

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

  /* Perform autonomous routine step */
  switch (autoRoutine) {

    case TestMinSpeed: {
        robot.drive().SetSpeed(0.03, 0.03);
    }; break;

    case Drive: {
      if (autoStep == 0)
      {
        robot.startDrive(2, 0.7);
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
      if (autoStep == 0)
      {
        robot.startWallFollow(60, 20, 0.75, SonarLoc::FrontRight);
        autoStep++;
      }
      else if (robot.mode() == Mode::WallFollowing)
      {
        robot.step();
      }
      else
      {
        autoRoutine = AutoRoutine::DoNothing;
      }
    }; break;

    case StopEndOfHallway: {
      if (autoStep == 0)
      {
        robot.drive().SetSpeed(0.6, 0.6);
        autoStep++;
      }
      else if (isEndOfHallway(SonarLoc::FrontRight)) {
        robot.stop();
        autoRoutine = AutoRoutine::DoNothing;
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
    PrintDrive();
    PrintGyro();
    PrintSonar();
    Serial.println();
  }
}

bool IsAutoMode() {
  const int BUSY_PIN = 33;
  return digitalRead(BUSY_PIN) == 0;
}

bool isEndOfHallway(SonarLoc sonarLoc) {
  constexpr float Threshold = 100;
  static float prevRange;
  static bool firstTime = true;

  float currRange = robot.sonar(sonarLoc).Range();

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
    + String(robot.sonar(SonarLoc::Front).Range()));
  Serial.println(" L/R Front = "
    + String(robot.sonar(SonarLoc::FrontLeft).Range()) + "\t"
    + String(robot.sonar(SonarLoc::FrontRight).Range()));
  Serial.println(" L/R Hall  = "
    + String(robot.sonar(SonarLoc::HallLeft).Range()) + "\t"
    + String(robot.sonar(SonarLoc::HallRight).Range()));
  Serial.println(" L/R Back  = "
    + String(robot.sonar(SonarLoc::BackLeft).Range()) + "\t"
    + String(robot.sonar(SonarLoc::BackRight).Range()));
  Serial.println("------------------------------\n");
}

void PrintDrive() {
  double leftDistance, rightDistance;
  double distance = robot.drive().GetDistance(leftDistance, rightDistance);
  Serial.println("------- Drive -------");
  Serial.println(" Distance = " + String(distance) + "m");
  Serial.println("  Left    = " + String(leftDistance) + "m");
  Serial.println("  Right   = " + String(rightDistance) + "m");
  Serial.println("---------------------\n");
}

void PrintGyro() {
  Serial.println("----- Gyroscope -----");
  Serial.println("Angle = " + String(robot.gyro().angleDeg()) + " deg");
  Serial.println("---------------------\n");
}
