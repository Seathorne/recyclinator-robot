void ReadLimits(){
  TopLimit= digitalRead(TopSwitch);           // read the top and bottom limit switches
  BottomLimit = digitalRead(BottomSwitch);

  // this next line is diagnostic only.
  if (ShowSwitches == true) Serial.println("Top: " + String(TopLimit) + "  Bottom: " + String(BottomLimit));

  // these lines stop the motor if a limitswitch is activated
  if ((BottomLimit == 0) && (Moving == true)&& (Direction == Down)) LiftMotorOff();
  if ((TopLimit == 0) && (Moving == true) && (Direction == Up)) LiftMotorOff();
}

  // called if the encoder has not changed state for 1.5 seconds.
void EncoderFail(){
  LiftMotorOff();
  Serial.println("Encoder Fail");
}

void ResetEncoderTimeout(){
  EncoderTimeout = millis()+1500;
}

void HandleCalibration(){
  Direction = Down;
  digitalWrite(Dir1,HIGH);
  digitalWrite(Dir2,LOW); 
  analogWrite(LiftMotor,100);  
  Moving = true;
  do                          // do loop waits for bottom switch to activate
    ReadLimits();
  while (BottomLimit == 1);   
  Counter = 0;                // reset encoder value
  // Now lift to top andcount pulses
  Direction = Up;
  digitalWrite(Dir2,HIGH);
  digitalWrite(Dir1,LOW); 
  analogWrite(LiftMotor,110);  
  Moving = true;
  do                          // do loop waits for bottom switch to activate
    ReadLimits();
  while (TopLimit == 1);    
  ReportEncoder();
  MaxCount = Counter;
  Calibrated = true;
  Moving = false;
}

