    

/*********************************************************
                         ARDUINO MEGA
                        RECYLINATOR III
                          Sonar Tests
                        19 November 2021

**********************************************************/

//   Program Pings an Ultrasonic Sensor and returns a distance in cm
//  Arduino pin assignments
int LeftHallSonar_pin   = 24;  //sonar #5
int RightHallSonar_pin  = 25;  //sonar #6
int LeftRearSonar_pin   = 26;  //sonar #2
int LeftFrontSonar_pin  = 27;  //sonar #1
int RightFrontSonar_pin = 28;  //sonar #4
int RightRearSonar_pin  = 29;  //sonar #3

float LeftHallRange;
float RightHallRange;
float LeftRearRange;
float LeftFrontRange;
float RightFrontRange;
float RightRearRange;

void setup() {

  Serial.begin(9600);
  pinMode(LeftHallSonar_pin, OUTPUT);
  pinMode(RightHallSonar_pin, OUTPUT);
  pinMode(LeftRearSonar_pin, OUTPUT);
  pinMode(LeftFrontSonar_pin, OUTPUT);
  pinMode(RightFrontSonar_pin, OUTPUT);
  pinMode(RightRearSonar_pin, OUTPUT); 
}

void loop() {
    LeftHallRange = SonarRange(LeftHallSonar_pin);
    Serial.print(LeftHallRange,0); 
    delay(20);

    LeftFrontRange = SonarRange(LeftFrontSonar_pin);
    Serial.write(9);
    Serial.print(LeftFrontRange,0); 
    delay(20); 

    LeftRearRange = SonarRange(LeftRearSonar_pin);
    Serial.write(9);
    Serial.print(LeftRearRange,0); 
    delay(20);          
  
    RightHallRange = SonarRange(RightHallSonar_pin);
    Serial.write(9);
    Serial.print(RightHallRange,0); 
    delay(20);  
 
    RightFrontRange = SonarRange(RightFrontSonar_pin);
    Serial.write(9);
    Serial.print(RightFrontRange,0); 
    delay(20);  
  
    RightRearRange = SonarRange(RightRearSonar_pin);
    Serial.write(9);
    Serial.println(RightRearRange,0); 
    delay(20);  
}
