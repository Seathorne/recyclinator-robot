void LiftMotorOff(){
  analogWrite(LiftMotor,0);
  digitalWrite(Dir1,LOW);
  digitalWrite(Dir2,LOW);
  Serial.println("LiftMotorOff");
  Moving = false;
}

void LiftUp(int s){
  if (Calibrated == false) return;                // don't start motor if not calibrated
  if (Counter > MaxCount-1) return;               // Can't go up if we are nearly at the top
  if (( s < MinSpeed) || (s > MaxSpeed)) return;  // can't set a speed below min or above max
  Speed = s;                                      // save speed
  Direction = Up;                                 // set direction value
  digitalWrite(Dir1,LOW);                         // set Dir pins correctly for this direction
  digitalWrite(Dir2,HIGH);                        // ...
  analogWrite(LiftMotor,Speed);                   // start the motor  
  Moving = true;                                  // flag moving
  ResetEncoderTimeout();                          // reset encoder failure test 
}

void LiftDown(int s){
  if (Calibrated == false) return;  
  if (Counter < 1 ) return;
  if (( s < MinSpeed) || (s > MaxSpeed)) return;  // can't set a speed below min or above max  Speed = s;
  Speed = s;
  Direction = Down;
  digitalWrite(Dir1,HIGH);
  digitalWrite(Dir2,LOW); 
  analogWrite(LiftMotor,Speed);  
  Moving = true;
  ResetEncoderTimeout();
}

void Lift(int pos,  int spd){
  if ((pos > MaxCount) || (pos < 0)) return;    // cant lift to impossible position
  LiftTarget = pos;                             // Save target position            
  if (LiftTarget > Counter){                    // decide which way to move motor
    SlowCount = LiftTarget - 100;
    LiftUp(spd);
  }
  if (LiftTarget < Counter){
    SlowCount = LiftTarget + 100;
    LiftDown(spd);
  }
}

// called from the loop if Moving is true
void HandleLift(){
  if (Direction == Up){
    if (Counter >=LiftTarget) LiftMotorOff();
    if (Counter >=SlowCount) analogWrite(LiftMotor,SlowValue);
  }
 if (Direction == Down){
    if (Counter <= LiftTarget) LiftMotorOff();
    if (Counter <= SlowCount) analogWrite(LiftMotor,SlowValue); 
 }
}

