
void Ping() {
  rangeRight = SonarRange(RightFrontSonar_pin);
}
//-----------------------------------------------------

float SonarRange(int sonar_pin) {
float echo;
float dist;
  pulseOut(sonar_pin);                      //sends out a ultrasonic pulse
  echo = pulseIn (sonar_pin, HIGH);         //times the return pulse
  dist = echo / 58.0;                       //converts round trip pulse time to distance in cm
  delay(20);
  return dist;
}
//-------------------------------------------------

void pulseOut(int pin) {
// SRF05 single pin mode  
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
}
