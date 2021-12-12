
void HandleCommand(){
  ParseInput();
  inputString = "";
  stringComplete = false;
  if (cmd == "s")                 LiftMotorOff();
  if (cmd == "lu")                LiftUp(arg[0]); 
  if (cmd == "ld")                LiftDown(arg[0]);   
  if (cmd == "e")                 ReportEncoder();                           // Show current encoder values
  if (cmd == "limit")             ReportLimits();
  if (cmd == "showswitches")      ShowSwitches = !ShowSwitches;
  if (cmd == "cal")               HandleCalibration();
  if (cmd == "lift")              Lift(arg[0],arg[1]);
}

/* cmd will hold the actual command string")
   arg[0-3] hold the data values being sent */
void ParseInput(){
  int space, slash;
  for(int x = 0; x < 4; x++) arg[x] = 0;
  ArgIndex = 0;
  space=inputString.indexOf(' ');
  slash = inputString.indexOf('\n');
  inputString = inputString.substring(0,slash);
  cmd = inputString.substring(0,space);
  inputString = inputString.substring(space+1,slash); 
  while (inputString.indexOf(' ') > 0){
    space = inputString.indexOf(' ');
    arg[ArgIndex] = inputString.substring(0,space).toInt();
    inputString = inputString.substring(space+1,inputString.length());
   ArgIndex++;   
  }
  arg[ArgIndex] = inputString.toInt();
 }

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
      HandleCommand();
    }
  } 
}



