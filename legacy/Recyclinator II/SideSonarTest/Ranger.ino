
void Ranger () {
//  Uses the side sonars to find the distance and angles to right and left hallway walls
//  ranges rounded to nearest cm
    delay(20);    
    pinMode(RtF_TrigEchopin, OUTPUT);
    pulseOut(RtF_TrigEchopin, trigPulse);
    pinMode(RtF_TrigEchopin, INPUT);    
    rangeRtF = pulseIn (RtF_TrigEchopin, HIGH)/58.0;
    
    delay(20);
    pinMode(RtR_TrigEchopin, OUTPUT);
    pulseOut(RtR_TrigEchopin, trigPulse);
    pinMode(RtR_TrigEchopin, INPUT);    
    rangeRtR = pulseIn (RtR_TrigEchopin, HIGH)/58.0;

    delay(20);    
    pinMode(LtF_TrigEchopin, OUTPUT);
    pulseOut(LtF_TrigEchopin, trigPulse);
    pinMode(LtF_TrigEchopin, INPUT);    
    rangeLtF = pulseIn (LtF_TrigEchopin, HIGH)/58.0;

    delay(20);
    pinMode(LtR_TrigEchopin, OUTPUT);
    pulseOut(LtR_TrigEchopin, trigPulse);
    pinMode(LtR_TrigEchopin, INPUT);    
    rangeLtR = pulseIn (LtR_TrigEchopin, HIGH)/58.0;
}

//---------------------------------------------------------

void pulseOut(int pin, int duration) {
  digitalWrite(pin, LOW);
  delayMicroseconds(12);
  digitalWrite(pin, HIGH);
  delayMicroseconds(duration);
  digitalWrite(pin, LOW);
}
           
