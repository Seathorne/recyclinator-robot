void InitialiseSerialPorts(){
  Serial.begin(9600);                    //Monitor
  Serial1.begin(57600);                  //Logomatic communications
  Serial2.begin(9600);                   //MD49 Motor Controller
}

void SetPinModes(){
  pinMode(rc_active, INPUT);            // zero in Auto mode
/*  
  pinMode(LtF_TrigEchopin, OUTPUT);
  pinMode(RtF_TrigEchopin, OUTPUT);
  pinMode(LtR_TrigEchopin, OUTPUT);
  pinMode(RtR_TrigEchopin, OUTPUT);
*/
}
