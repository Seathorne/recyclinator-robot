  
void SetPinModes() {  
  pinMode(rc_active, INPUT);            // zero in Auto mode
  pinMode(LidarPwrEn_pin, OUTPUT);
  pinMode(LidarMonitor_pin, INPUT);
  pinMode(LidarTrigger_pin, OUTPUT);

  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
  digitalWrite(30, LOW);
  digitalWrite(31, LOW);
  digitalWrite(32, LOW);
  LidarServo.attach(7);    
}  


