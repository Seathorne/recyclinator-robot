  
void SetPinModes() {  
  pinMode(rc_active, INPUT);            // zero in Auto mode
  pinMode(LidarPwrEn_pin, OUTPUT);
  pinMode(LidarMonitor_pin, INPUT);
  pinMode(LidarTrigger_pin, OUTPUT);

  LidarServo.attach(7);    
}  


