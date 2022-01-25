#include "Lidar.h"
#define SERVOMIN 120
#define SERVOMAX 475
//////////lidar class///////////////////////////////////////////////

//constructor//////////////////////////////////////////////////
Lidar::Lidar(){}
//End of Constructor Section///////////////////////////////////
//Initialiser//////////////////////////////////////////////////
void Lidar::Start(int pwmcode, int UpSwitch, int DownSwitch, int UpDirect, int DownDirect, int LiftMotor, int Encoder)
{
  this->begin(0, true); //this should handle the Lidar's configuration.
    
  pwm = Adafruit_PWMServoDriver(pwmcode); //This should handle the PWM's configuration.
  pwm.begin();     //PWM Begin
  pwm.setPWMFreq(50);  //Hz set
      
  pinMode(UpSwitch, INPUT_PULLUP); //all this setup for some switches
  pinMode(DownSwitch, INPUT_PULLUP); //likewise
  pinMode(UpDirect, OUTPUT);  //lift up/down
  pinMode(DownDirect, OUTPUT);   //lift down/up
  analogWrite(LiftMotor,0);  //lift motor
  pinMode(Encoder,INPUT_PULLUP);  //setting up encoder
  
  TopSwitch=UpSwitch;
  BottomSwitch=DownSwitch;
  Dir1=UpDirect;
  Dir2=DownDirect;      
  LiftMotor=LiftMotor;
  Encode=Encoder;
  TargetCount=-1;
}
void Lidar::Start()
{
  begin(0, true); //this should handle the Lidar's configuration.
    
  pwm = Adafruit_PWMServoDriver(0x41); //This should handle the PWM's configuration.
  pwm.begin();     //PWM Begin
  pwm.setPWMFreq(50);  //Hz set
      
  pinMode(22, INPUT_PULLUP); //all this setup for some switches
  pinMode(23, INPUT_PULLUP); //likewise
  pinMode(6, OUTPUT); //lift up/down
  pinMode(5, OUTPUT);   //lift down/up
  analogWrite(4,0);  //lift motor
  pinMode(2,INPUT_PULLUP);
  
  TopSwitch=22;
  BottomSwitch=23;
  Dir1=6;
  Dir2=5;     
  LiftMotor=4;
  Encode=2;
  TargetCount=-1;
}
      //Initialiser/////////////////////////////////////////////////

     
void  Lidar::Update()
  {
  	_range = distance(false);
  }
void Lidar::ReadLimits()
	{
  	int TopLimit= digitalRead(TopSwitch);           // read the top and bottom limit switches
  	int BottomLimit = digitalRead(BottomSwitch);
  	
  	// these lines stop the motor if a limitswitch is activated
  	if ((BottomLimit == 0) && (Moving == true) && (Direction==1)) LiftMotorOff();
  	if ((TopLimit == 0) && (Moving == true) && (Direction==2)) LiftMotorOff();
	}
	//likewise//
  void Lidar::HandleCalibration()
  {
  ResetEncoderTimeout();
  digitalWrite(Dir1,HIGH); //toggle direction to down.
  digitalWrite(Dir2,LOW); 
  analogWrite(LiftMotor,100);  
  Direction=1;
  Moving = true;
  do                          // do loop waits for bottom switch to activate
  ReadLimits();
  while (Moving==true);   
  Counter = 0;                // reset encoder value
  // Now lift to top and count pulses
  digitalWrite(Dir1,LOW); //toggle direction to up.
  digitalWrite(Dir2,HIGH);
  analogWrite(LiftMotor,110);  
  Direction=2;
  Moving = true;
  do                          // do loop waits for top switch to activate
  ReadLimits();
  while (Moving==true);    
  MaxCount = Counter;
  Calibrated = true;
  Serial.println(MaxCount);
}

void Lidar::LiftMotorOff()
{
  analogWrite(LiftMotor,0);
  digitalWrite(Dir1,LOW);
  digitalWrite(Dir2,LOW);
  Moving=false; 
}

void Lidar::UpdateEncoder(){
//  if(EncoderTimeout<millis()) LiftMotorOff();
  if ((Counter < TargetCount+100 && Counter > TargetCount-100) && Calibrated==true)
  {
  LiftMotorOff();
  }
  if (Direction == 2) Counter++;
  if (Direction == 1) Counter--;

  ResetEncoderTimeout();
  
}

void Lidar::ResetEncoderTimeout(){
  EncoderTimeout = millis()+1500;
}

void Lidar::MoveTo(int pos)
{
  TargetCount=pos;
if(pos<0 || pos>MaxCount || Calibrated==false)  //if not calibrated or position is less than 0 or position is more than MaxCount
{
   Serial.print("H case");
  return;                 //return
}
else if(pos>Counter)  //if direction is up
{
  Serial.print("R case");
  ResetEncoderTimeout();
  Moving = true;
  digitalWrite(Dir1,LOW); //toggle direction to up.
  digitalWrite(Dir2,HIGH);
  analogWrite(LiftMotor,110);  
  Direction=2;
}
else if(pos<Counter)  //if direction is down
{
  Serial.print("W case");
  ResetEncoderTimeout();
  Moving=true;
  digitalWrite(Dir1,HIGH); //toggle direction to down.
  digitalWrite(Dir2,LOW); 
  analogWrite(LiftMotor,100);  
  Direction=1;
}
else
{
  Serial.println(pos);
  Serial.println(Counter);
  return;
}
}
void Lidar::MoveBy(int num)
{
  int temp;
  temp=Counter+num;     //pointless but ultimately it's what we need I guess.
  MoveTo(temp);
}
int Lidar::Point(float ang) {
int pulsePWM = 0;
  if(ang < 0)   ang = 0.0;
  if(ang > 180) ang = 180.0;
  Angle=ang;
  pulsePWM = int(SERVOMIN + (ang/180)*(SERVOMAX - SERVOMIN));

  return pulsePWM;
}

void Lidar::RotateTo(int pos)
{
    pulselen = Point(pos);
    pwm.setPWM(servonum, 0, pulselen);
}
void Lidar::RotateBy(int num)
{
  Angle=Angle+num;
  RotateTo(Angle);
}
///////////////////////////////////////////////////////////////////////
