void HandleCommand(){
  ParseInput();
  inputString = "";
  if (cmd == "angles")      SetAngles(arg[0],arg[1], arg[2]);
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
    inputString += inChar;                  // add it to the inputString:
    if (inChar == '\n') {
      HandleCommand();
    }
  } 
}

void SetAngles(int Go, int A1, int A2){
  go = Go;
  Gamma[1] = A1;
  Gamma[2] = A2;
}

