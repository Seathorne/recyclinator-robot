
byte lowBit = 8;
byte highBit = 9;
byte relayLeft = 6;
byte relayRight = 7;
byte lowVal;
byte highVal;
byte leftVal;
byte rightVal;

void setup() {
  pinMode(lowBit, INPUT);
  pinMode(highBit, INPUT);
  pinMode(relayLeft, OUTPUT);
  pinMode(relayRight, OUTPUT);

  digitalWrite(relayLeft, LOW);
  digitalWrite(relayRight, LOW);
}

void loop() {
  lowVal = digitalRead(lowBit);
  highVal = digitalRead(highBit);
  if ((lowVal == 0) && (highVal == 0)) {
    leftVal = LOW;
    rightVal = LOW;
  }
  else if ((lowVal == 0) && (highVal == 1)) {
    leftVal = HIGH;
    rightVal = LOW;
  }
  else if ((lowVal == 1) && (highVal == 0)) {
    leftVal = LOW;
    rightVal = HIGH;
  }
  else if ((lowVal = 1) && (highVal == 1)) {
    leftVal = HIGH;
    rightVal = HIGH;
  }
  flash();
}

void flash()  {
  digitalWrite(relayLeft, leftVal);
  digitalWrite(relayRight, rightVal);  
  delay(500);
  digitalWrite(relayLeft, LOW);
  digitalWrite(relayRight, LOW);    
  delay(500);
}


