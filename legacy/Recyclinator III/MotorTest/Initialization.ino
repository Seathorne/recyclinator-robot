
/*   FUNCTIONS
     1. void SetPinModes()             -  line 10
     2.  void InitializeSerialPorts()  -  line 15 22
*/

//-----------------------------------------

void SetPinModes () {
  pinMode(rc_active, INPUT);            // zero in Auto mode
}

//--------------------------------------------
void InitializeSerialPorts(){
  Serial.begin(9600);                    //Monitor
  Serial1.begin(57600);                   //Logomatic communications
  Serial2.begin(9600);                   //MD49 Motor Controller
}
