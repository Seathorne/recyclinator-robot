
boolean PeriodState = false;

byte lowBit = 8;
byte highBit = 9; 
byte enable = 10;
byte relayLeft = 6;
byte relayRight = 7;
byte relay3 = 5;
byte relay4 = 4;
byte lidarOne = A1;
byte lidarTwo = A2;
byte lidarThree = A3;
byte lidarFour = A4;
byte lidarFive = A5;
byte lowVal;
byte highVal;
byte leftVal;
byte rightVal;
byte enableVal;

float valLidarOne;
float valLidarTwo;
float valLidarThree;
float valLidarFour;
float valLidarFive;

unsigned long PeriodTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(lowBit, INPUT);
  pinMode(highBit, INPUT);
  pinMode(enable, INPUT);
  pinMode(relayLeft, OUTPUT);
  pinMode(relayRight, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

  pinMode(lidarOne, OUTPUT);
  pinMode(lidarTwo, OUTPUT);
  pinMode(lidarThree, OUTPUT);
  pinMode(lidarFour, OUTPUT);
  pinMode(lidarFive, OUTPUT);

  digitalWrite(relayLeft, LOW);
  digitalWrite(relayRight, LOW);
  digitalWrite(enable, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
}

void loop() {
  LidarBump();
  Serial.print(valLidarOne);
  Serial.write(9);
  Serial.print(valLidarTwo);
  Serial.write(9);
  Serial.print(valLidarThree);
  Serial.write(9);
  Serial.print(valLidarFour);
  Serial.write(9);
  Serial.println(valLidarFive);
  delay(100);
  enableVal = digitalRead(enable);
  if((millis() > PeriodTime) && (enableVal == 1)) {  
    flash();
  }
  if (enableVal == 0) {
    digitalWrite(relayLeft, LOW);
    digitalWrite(relayRight, LOW);
  }

}

void flash()  {
    PeriodTime = millis() + 500;
    if (PeriodState == false) {
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


