
float SonarRange(int sonar_pin) {
float echo;  
float range;
  pulseOut(sonar_pin);                      //sends out a ultrasonic pulse
  pinMode(sonar_pin, INPUT);
  echo = pulseIn (sonar_pin, HIGH);         //times the return pulse
  range = echo/58.0;                        //converts round trip pulse time to distance
  delay(50);  
  return range;
}

//pings the ultrasonic sensor
void pulseOut(int pin) {
  pinMode(pin, OUTPUT);  
  digitalWrite(pin, HIGH);
  delayMicroseconds(12);
  digitalWrite(pin, LOW);
}
