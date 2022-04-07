/*
 *       Recyclinator Lift Controller 
 *       After Uploading the Program Type "cal" in the Serial Monitor send line
 *       After calibrating, the lift is operated by typing lift pos speed in the command line
 *       The position must be between zero (bottom position), and the upper position indicated
 *        on the monitor after calibration.
 *       The speed may be between 90 and 255.
 */
// I/O pin assignmentsch = 22;
int BottomS;
int TopSwitch = 22;
int BottomSwitch = 23;
int Dir1 = 6;
int Dir2 = 5;
int LiftMotor = 4;


int Off = 0;                // constant value for Off
int Up = 1;                 // constant value for Up
int Down = 2;               // constant value for Down
int Direction = Off;        // uses the variables above
boolean Moving = false;     // true if the motor is meant to be turning
int Speed = 0;              // speed to move motor
int MinSpeed = 90;          // minimum speed. Motor may not start below that value
int MaxSpeed = 255;          // maximum speed.


// Previously recorded limit switch positions
// 1 = open (not pressed)
// 0 = pressed
int TopLimit;
int BottomLimit;
int OldTopLimit = 1;
int OldBottomLimit = 1;
boolean ShowSwitches = false;

int volatile Counter = 0;             //lift encoder count
boolean Calibrated = false;           // true if the lift has been calibrated
unsigned long EncoderTimeout = 200;   // 200ms of no encoder data when Moving = true causes a failure
int MaxCount = 0;                     // top of the lift as calculated during calibration
int SlowCount;                        // value to start slowing the lift
int LiftTarget = 0;                   // the target position for the lift
int SlowValue = 90;                    // the speed to slow to for the last bit of the lift operation

//--------------------- SERIAL COMMAND SYSTEM -------------------------------
String cmd = "";                      // the Command 
long arg[4] = {0,0,0,0};              // you can pass up to 4 arguments in a command
int ArgIndex;                         // index into arguments
String inputString = "";              // a string to hold incoming data
boolean stringComplete = false;       // whether the string is complete

void setup() {
  Serial.begin(9600);
  pinMode(TopSwitch, INPUT_PULLUP);
  pinMode(BottomSwitch, INPUT_PULLUP);
  pinMode(Dir1, OUTPUT);
  pinMode(Dir2, OUTPUT);  
  analogWrite(LiftMotor,0);
  pinMode(2,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), UpdateEncoder, CHANGE);     
  Serial.println("LiftControl V1.0");

}

void loop() {
  ReadLimits();
  delay(5);
  if ((Moving == true) && (millis() > EncoderTimeout)) EncoderFail();
  if (Moving == true) HandleLift();
}

void UpdateEncoder(){
  if (Direction == Up) Counter++;
  if (Direction == Down) Counter--;
  ResetEncoderTimeout();
  
}
