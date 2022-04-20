#include "Robot.h"

enum AutoRoutine
{
  DoNothing,
  ActionList,
  Drive,
  Rotate,
  WallFollow,
  WallFollowFeatureDetect,
  StopEndOfHallway,
  RotateDrive,
  TestMinSpeed,
  EndHallwayRightTurn,
  EndHallwayFeatureDetect,
  TestFeatureDetection,
  WallCompTest
};

Robot robot;
AutoRoutine autoRoutine = AutoRoutine::WallCompTest;

void setup() {
  Serial.begin(9600);

  /* Initialize static classes */
  // Junctions::Init();

  /* Initialize subsystems */
  robot.init();

  Serial.println("Robot| setup complete.");
}

void loop() {
  constexpr long FrameLength = 100;
  constexpr bool PrintAll = true;
  float testSetPoint[2];
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

    case WallFollowFeatureDetect: {
      const static constexpr float RangeSetpoint = 60;
      
      static Feature feature;
      static float featureRange;
      
      switch (autoStep) {
        case 0:
          Serial.println("Auto| step 0: start wall following");
          robot.startWallFollow(RangeSetpoint, -1, 0.7, SonarLoc::FrontRight);
          autoStep++;
          break;
        case 1:
          Serial.println("Auto| step 1: continue wall following");
          
          feature = robot.detectFeatureRepeated(SonarLoc::HallRight, featureRange);
          switch (feature) {
            case Feature::Junction:
              Serial.println("Auto| step 1: end of hallway detected");
              robot.stop();
              break;
            case Feature::Other:
              Serial.println("Auto| step 1: feature detected");
              robot.setRangeSetpoint(featureRange); // adjust range setpoint
              // no break is intentional
            default:
              if (robot.mode() == Mode::WallFollowing) {
                robot.step();
              } else {
                Serial.println("Auto| step 1: wall following complete");
                robot.stop();
                autoRoutine = AutoRoutine::DoNothing;
              };
              break;
          }
          break;
      }
    } break;

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
          break;
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
          break;
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

    case EndHallwayRightTurn: {
      switch (autoStep) {
        case 0:
          Serial.println("Auto| step 0: start wall following");
          robot.startWallFollow(60, -1, 0.7, SonarLoc::FrontRight);
          autoStep++;
          break;
        case 1:
          Serial.println("Auto| step 1: continue wall following");
          if (isEndOfHallway(SonarLoc::FrontRight)) {
            Serial.println("Auto| step 1: end of hallway detected");
            robot.stop();
          } else if (robot.mode() == Mode::WallFollowing) {
            robot.step();
          } else {
            Serial.println("Auto| step 1: wall following complete");
            autoStep++;
          };
          break;
        case 2:
          Serial.println("Auto| step 2: starting rotation");
          robot.startRotate(45);
          autoStep++;
          break;
        case 3:
          Serial.println("Auto| step 3: continuing rotation");
          if (robot.mode() == Mode::Rotating) {
            robot.step();
          } else {
            Serial.println("Auto| step 3: rotation complete");
            autoStep++;
          }
          break;
        case 4:
          Serial.println("Auto| step 4: starting drive");
          robot.startDrive(0.5, 0.5);
          autoStep++;
          break;
        case 5:
          Serial.println("Auto| step 5: continuing drive");
          if (robot.mode() == Mode::Driving) {
            robot.step();
          } else {
            Serial.println("Auto| step 5: drive complete");
            autoStep++;
          }
          break;
        case 6:
          Serial.println("Auto| step 6: starting rotation");
          robot.startRotate(45);
          autoStep++;
          break;
        case 7:
          Serial.println("Auto| step 7: continuing rotation");
          if (robot.mode() == Mode::Rotating) {
            robot.step();
          } else {
            Serial.println("Auto| step 7: rotation complete");
            autoStep++;
          }
          break;
        case 8:
          Serial.println("Auto| step 8: starting drive");
          robot.startDrive(1, 0.7);
          autoStep++;
          break;
        case 9:
          Serial.println("Auto| step 9: continuing drive");
          if (robot.mode() == Mode::Driving) {
            robot.step();
          } else {
            Serial.println("Auto| step 9: drive complete");
            autoStep++;
          }
          break;
        case 10:
          Serial.println("Auto| step 10: start wall following");
          robot.startWallFollow(60, -1, 0.7, SonarLoc::FrontRight);
          autoStep++;
          break;
        case 11:
          Serial.println("Auto| step 11: continue wall following");
          if (isEndOfHallway(SonarLoc::FrontRight)) {
            Serial.println("Auto| step 11: end of hallway detected");
            robot.stop();
          } else if (robot.mode() == Mode::WallFollowing) {
            robot.step();
          } else {
            Serial.println("Auto| step 11: wall following complete");
            autoStep++;
          };
          break;
      }
    }; break;

    case EndHallwayFeatureDetect: {
      const static constexpr float RangeSetpoint = 60;
      
      static Feature feature;
      static float featureRange;
      
      switch (autoStep) {
        case 0:
          Serial.println("Auto| step 0: start wall following");
          robot.startWallFollow(RangeSetpoint, -1, 0.7, SonarLoc::FrontRight);
          autoStep++;
          break;
        case 1:
          Serial.println("Auto| step 1: continue wall following");
          
          feature = robot.detectFeatureRepeated(SonarLoc::FrontRight, featureRange);
          switch (feature) {
            case Feature::Junction:
              Serial.println("Auto| step 1: end of hallway detected");
              robot.stop();
              break;
            case Feature::Other:
              Serial.println("Auto| step 1: feature detected");
              robot.setRangeSetpoint(featureRange); // adjust range setpoint
              // no break is intentional
            default:
              if (robot.mode() == Mode::WallFollowing) {
                robot.step();
              } else {
                Serial.println("Auto| step 1: wall following complete");
                autoStep++;
              };
              break;
          }
          
          break;
        case 2:
          Serial.println("Auto| step 2: starting rotation");
          robot.startRotate(45);
          autoStep++;
          break;
        case 3:
          Serial.println("Auto| step 3: continuing rotation");
          if (robot.mode() == Mode::Rotating) {
            robot.step();
          } else {
            Serial.println("Auto| step 3: rotation complete");
            autoStep++;
          }
          break;
        case 4:
          Serial.println("Auto| step 4: starting drive");
          robot.startDrive(0.5, 0.5);
          autoStep++;
          break;
        case 5:
          Serial.println("Auto| step 5: continuing drive");
          if (robot.mode() == Mode::Driving) {
            robot.step();
          } else {
            Serial.println("Auto| step 5: drive complete");
            autoStep++;
          }
          break;
        case 6:
          Serial.println("Auto| step 6: starting rotation");
          robot.startRotate(45);
          autoStep++;
          break;
        case 7:
          Serial.println("Auto| step 7: continuing rotation");
          if (robot.mode() == Mode::Rotating) {
            robot.step();
          } else {
            Serial.println("Auto| step 7: rotation complete");
            autoStep++;
          }
          break;
        case 8:
          Serial.println("Auto| step 8: starting drive");
          robot.startDrive(1, 0.7);
          autoStep++;
          break;
        case 9:
          Serial.println("Auto| step 9: continuing drive");
          if (robot.mode() == Mode::Driving) {
            robot.step();
          } else {
            Serial.println("Auto| step 9: drive complete");
            autoStep++;
          }
          break;
        case 10:
          Serial.println("Auto| step 10: start wall following");
          robot.startWallFollow(RangeSetpoint, -1, 0.7, SonarLoc::FrontRight);
          autoStep++;
          break;
        case 11:
          Serial.println("Auto| step 11: continue wall following");

          feature = robot.detectFeatureRepeated(SonarLoc::FrontRight, featureRange);
          switch (feature) {
            case Feature::Junction:
              Serial.println("Auto| step 11: end of hallway detected");
              robot.stop();
              break;
            case Feature::Other:
              Serial.println("Auto| step 11: feature detected");
              robot.setRangeSetpoint(featureRange); // adjust range setpoint
              // no break is intentional
            default:
              if (robot.mode() == Mode::WallFollowing) {
                robot.step();
              } else {
                Serial.println("Auto| step 11: wall following complete");
                autoStep++;
              };
              break;
          }
          
          break;
        case 12:
          Serial.println("Auto| step 12: routine complete");
          autoRoutine = AutoRoutine::DoNothing;
          robot.stop();
          break;
      }
    }; break;
	
    case TestFeatureDetection: {
        if (autoStep == 0)
      {
        robot.startDrive(2, 0.7);
        autoStep++;
      }
      else if (robot.mode() == Mode::Driving)
      {
        float rangeLeft, rangeRight;
        
        Feature left = robot.detectFeatureRepeated(SonarLoc::HallLeft, rangeLeft);
        if (left != Feature::None)
        {
          Serial.println("Test Feature Detection| Left Feature = " + String(left) + ", Range = " + String(rangeLeft) + " cm");
        }
        
        Feature right = robot.detectFeatureRepeated(SonarLoc::HallRight, rangeLeft);
        if (right != Feature::None)
        {
          Serial.println("Test Feature Detection| Right Feature = " + String(right) + ", Range = " + String(rangeRight) + " cm");
        }

        robot.step();
      }
      else
      {
        autoRoutine = AutoRoutine::DoNothing;
      }
    }; break;

    case WallCompTest: {
    const static constexpr float RangeSetpoint = 60;
    
    static Feature feature;
    static float featureRange;
    
    switch (autoStep) {
      case 0:
        Serial.println("Auto| step 0: start wall following");
        robot.startWallFollowComp(RangeSetpoint, -1, 0.7, SonarLoc::HallRight, SonarLoc::HallLeft);
        autoStep++;
        break;
      case 1:
        Serial.println("Auto| step 1: continue wall following");
        
        if(robot.checkWall(SonarLoc::HallRight, SonarLoc::HallLeft))                                                      //reset case
        {
          Serial.println("Reset case. If this occurs, the robot *should* be between two consistent walls.");
          robot.setRangeSetpoint(RangeSetpoint);
          Serial.println("Range Setpoint set to"+String(RangeSetpoint));
          feature=Feature::None;
        }
        else
        {
        
          feature = robot.detectFeatureRepeatedComp(SonarLoc::HallRight, SonarLoc::HallLeft, featureRange);
        }
          switch (feature) {
            case Feature::Junction:
              Serial.println("Auto| step 1: end of hallway detected");
              robot.stop();
              Serial.println("Auto| step 1: wall following complete");
              autoStep++;
              break;
            case Feature::Other:
              Serial.println("Auto| step 1: feature detected");
              robot.setRangeSetpoint(featureRange-(testSetPoint[0]-robot.getRangeSetpoint())); // adjust range setpoint
              // no break is intentional
            default:
              testSetPoint[0]=testSetPoint[1];
              testSetPoint[1]=featureRange;
              Serial.println("Range set to" + String(RangeSetpoint));
              if (robot.mode() == Mode::WallFollowing) {
                robot.step();
              } else {
                Serial.println("Auto| step 1: wall following complete");
                autoStep++;
              };
              break;
          }
        
        
        break;
      case 2:
        Serial.println("Auto| step 2: starting rotation");
        robot.startRotate(45);
        autoStep++;
        break;
      case 3:
        Serial.println("Auto| step 3: continuing rotation");
        if (robot.mode() == Mode::Rotating) {
          robot.step();
        } else {
          Serial.println("Auto| step 3: rotation complete");
          autoStep++;
        }
        break;
      case 4:
        Serial.println("Auto| step 4: starting drive");
        robot.startDrive(0.5, 0.5);
        autoStep++;
        break;
      case 5:
        Serial.println("Auto| step 5: continuing drive");
        if (robot.mode() == Mode::Driving) {
          robot.step();
        } else {
          Serial.println("Auto| step 5: drive complete");
          autoStep++;
        }
        break;
      case 6:
        Serial.println("Auto| step 6: starting rotation");
        robot.startRotate(45);
        autoStep++;
        break;
      case 7:
        Serial.println("Auto| step 7: continuing rotation");
        if (robot.mode() == Mode::Rotating) {
          robot.step();
        } else {
          Serial.println("Auto| step 7: rotation complete");
          autoStep++;
        }
        break;
      case 8:
        Serial.println("Auto| step 8: starting drive");
        robot.startDrive(1, 0.7);
        autoStep++;
        break;
      case 9:
        Serial.println("Auto| step 9: continuing drive");
        if (robot.mode() == Mode::Driving) {
          robot.step();
        } else {
          Serial.println("Auto| step 9: drive complete");
          autoStep=0;
        }
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
