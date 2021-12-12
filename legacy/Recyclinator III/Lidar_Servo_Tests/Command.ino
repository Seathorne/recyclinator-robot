
// This Module waits for an input from the Serial Monitor
// The input value is used to point the Lidar in the main program

void HandleCommand(){
  ParseInput();
  inputString = "";
// for calc;  arg[0] = servoAngle
  if (cmd == "ang")      SetAngle(arg[0]);
}

/* cmd will hold the actual command string")
   arg[0] hold the data value being sent */
void ParseInput(){
  int space, slash;
  for(int x = 0; x < 3; x++) arg[x] = 0;
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
    inputString += inChar;                  // add it to the inputString:
    if (inChar == '\n') {
      HandleCommand();
    }
  } 
}

void SetAngle(int A0){
  go = 1;
  servoAng = A0; 
}
