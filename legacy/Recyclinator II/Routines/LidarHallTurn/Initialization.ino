  
void SetPinModes() {  
  pinMode(rc_active, INPUT);            // zero in Auto mode
  pinMode(LidarPwrEn_pin, OUTPUT);
  pinMode(LidarMonitor_pin, INPUT);
  pinMode(LidarTrigger_pin, OUTPUT);

//  Following to prevent turn signal blinking during testing
  pinMode(TurnLow, OUTPUT);
  pinMode(TurnHigh, OUTPUT);
  pinMode(TurnEn,OUTPUT);

  digitalWrite(TurnLow, LOW);
  digitalWrite(TurnHigh, LOW);
  digitalWrite(TurnEn, LOW);

  LidarServo.attach(7);    
}  


