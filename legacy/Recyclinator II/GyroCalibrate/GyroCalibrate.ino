
/*
  "Calibrate" encoders and gyro pivoting around one wheel in a circle.
*/

#define  Left      0        // values for wall follow side
#define  Right     1

byte SynchByte = 0x00; 
byte SetMode = 0x34;
byte rc_active = 33;         //Signal from BX-24 indicating R/C Control when high
byte busy;
byte MtrStop = 128;
byte LtMtrSpd;
byte RtMtrSpd;
byte go;
byte turnDir;
byte MtrTurn;

float gyroAngle;

long encoderLt;
long encoderRt;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(19200);
  pinMode(rc_active, INPUT); 
  ConfigMotors();  
  SetAcceleration(3); 
  go = 0;  
  turnDir = L veft;
  MtrTurn = 106;
  EncRst();
}

void loop() {
    busy = digitalRead(rc_active);          //busy = 0 when in Auto Mode
      if(busy == 0) { 
        Serial3.write('Z');  
        delay(50); 
        while(Serial3.read() >= 0);  
        gyroAngle = 0;       
        if (go == 0) {
          EncRst();
          while ((abs(encoderLt) <= 5100) && (abs(encoderRt) <= 5100)) {  
            GyroTurn(turnDir);    
            MtrSpeed(LtMtrSpd, RtMtrSpd);            
            Encoders(encoderLt, encoderRt);            
            Serial.print(encoderLt);
            Serial.write(9);
            Serial.print(encoderRt);
            Serial.write(9);
            Serial.println(gyroAngle,0);
          }
        go = 1;
        } 
    }
}
