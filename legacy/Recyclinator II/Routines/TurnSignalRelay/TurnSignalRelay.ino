
boolean PeriodState = false;

byte lowBit = A0;
byte highBit = A1;
byte enable = A2;
byte relayLeft = 4;
byte relayRight = 5;
byte lowVal;
byte highVal;
byte leftVal;
byte rightVal;
byte enableVal;

unsigned long PeriodTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(lowBit, INPUT);
  pinMode(highBit, INPUT);
  pinMode(enable, INPUT);
  pinMode(relayLeft, OUTPUT);
  pinMode(relayRight, OUTPUT);

  digitalWrite(relayLeft, LOW);
  digitalWrite(relayRight, LOW);
  digitalWrite(enable, LOW);
}

void loop() {
  enableVal = digitalRead(enable);
  if((millis() > PeriodTime) && (enableVal == 1)) {  
    flash();
  }
/*  
  if (enableVal == 0) {
    digitalWrite(relayLeft, LOW);
    digitalWrite(relayRight, LOW);
  }
*/
}

void flash()  {
    PeriodTime = millis() + 500;
    if (PeriodState == false) {
        lowVal = digitalRead(lowBit);
        highVal = digitalRead(highBit);
        Serial.print(lowVal);
        Serial.write(9);
        Serial.println(highVal);
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
      digitalWrite(relayLeft, leftVal);
      digitalWrite(relayRight, rightVal); 
      PeriodState = true;
    }
    else {
      PeriodState = false;
      digitalWrite(relayLeft, LOW);
      digitalWrite(relayRight, LOW); 
    }
}


