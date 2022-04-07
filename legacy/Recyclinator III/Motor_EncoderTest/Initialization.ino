
/*   FUNCTIONS
     1. void SetPinModes()             -  line  8
     2.  void InitializeSerialPorts()  -  line 13
*/
//-----------------------------------------

void SetPinModes () {
  pinMode(rc_active, INPUT);            // zero in Auto mode
}
//--------------------------------------------

void InitializeSerialPorts(){
  Serial.begin(9600);                    //Monitor
  Serial1.begin(19200);                  //Logomatic communications
  Serial2.begin(9600);                   //MD49 Motor Controller
}

 
