void HandleCommand(){
  ParseInput();
  inputString = "";
// for calc;  arg[0] = number of angles;  arg[1] = alpha  
  if (cmd == "ang")      SetAngles(arg[0], arg[1]);
}


/* cmd will hold the actual command string")
   arg[0-3] hold the data values being sent */
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

void SetAngles(int A0, int A1){
  Serial.print(A0);
  Serial.write(9);
  Serial.println(A1);

  Serial1.print(A0);
  Serial1.write(9);
  Serial1.println(A1);  
  go = 1;
//  alpha (deg) measured CW from left perpendicular to heading    
  num = A0;
  alpha = A1; 
}

