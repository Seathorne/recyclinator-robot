
byte lowBit = 32;
byte highBit = 33;
byte relayLeft = 31;
byte relayRight = 30;

void setup() {
  pinMode(lowBit, OUTPUT);
  pinMode(highBit, OUTPUT);
  pinMode(relayLeft, OUTPUT);
  pinMode(relayRight, OUTPUT);

  digitalWrite(relayLeft, LOW);
  digitalWrite(relayRight, LOW);
}

void loop() {
  digitalWrite(relayLeft, LOW);
  digitalWrite(relayRight, LOW);  
  delay(500);
  digitalWrite(relayLeft, LOW);
  digitalWrite(relayRight, LOW);    
  delay(500);
}
