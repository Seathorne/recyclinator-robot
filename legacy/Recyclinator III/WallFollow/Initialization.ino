
void SetPinModes () {
  pinMode(rc_active, INPUT);            // zero in Auto mode
  pinMode(RightFrontSonar_pin, OUTPUT);  
}
//--------------------------------------------

void InitializeSerialPorts(){
  Serial.begin(9600);                    //Monitor
  Serial1.begin(19200);                  //Logomatic communications
  Serial2.begin(9600);                   //MD49 Motor Controller
}

 
