//EXPERIMENTAL BRANCH

#include "Action.h"
#include "DriveAction.h"
//#include "Junctions.h"
#include "Robot.h"

enum AutoRoutine
{
  WallCompTest
};

Robot robot;
AutoRoutine autoRoutine = AutoRoutine::WallCompTest;

constexpr int ACTIONS = 1;
Action *actions[ACTIONS] = { new DriveAction(&robot, 2, 0.7) };

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

    case WallCompTest: 
    const static constexpr float RangeSetpoint = 60;
    const static constexpr float RangeSetpointL= 141;
    static Feature feature;
    static Feature featureL;
    static float featureRange;
    static float featureRangeL;
    static bool flip;
    static int cases;
    switch (autoStep) {
      case 0:
        Serial.println("Auto| step 0: start wall following");
        robot.startWallFollowComp(RangeSetpoint, RangeSetpointL, -1, 0.7, SonarLoc::HallRight, SonarLoc::HallLeft);
        autoStep++;
        break;
      case 1:
        Serial.println("Auto| step 1: continue wall following");
        
        if(robot.checkWall(SonarLoc::HallRight, SonarLoc::HallLeft))                                                      //base case
        {
          Serial.println("Reset case. If this occurs, the robot *should* be between two consistent walls.");
          robot.setRangeSetpoint(RangeSetpoint);
          Serial.println("Range Setpoint set to"+String(RangeSetpoint));
          feature=Feature::None;
          flip=false;
        }
        else
        {
        
        feature = robot.detectFeatureRepeatedComp(SonarLoc::HallRight, SonarLoc::HallLeft, featureRange);
        featureL= robot.detectFeatureRepeatedComp(SonarLoc::HallLeft, SonarLoc::HallRight, featureRangeL);
        }
        if(feature==Feature::Junction || featureL==Feature::Junction) //junction case
        {
          case=4;
        }
        if(feature==Feature::Other) // right feature nonconsistency 
        {
          flip==true;
          case=3;
        }
        if(featureL==Feature::Other)  //left feature nonconsistency
        {
          flip==false;
          case=2;
        }
        else                           //default case
        {
          case=1;
          flip=false;
        }
        if(case!=4)
        {
        robot.step(flip);
        }
        else
        {
          robot.stop();
        }
        break; 
          /*
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
                robot.step(Flip);
              } else {
                Serial.println("Auto| step 1: wall following complete");
                autoStep++;
              };
              break;
              */
      } break;
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
