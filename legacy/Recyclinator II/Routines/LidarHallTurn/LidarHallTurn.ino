
#include <math.h>
#include <Servo.h>
Servo LidarServo;               //Left write(129);  Forward write(87);  Right write(45)

#define  faceLeft    129    // values for Lidar servo position
#define  faceForward 87
#define  faceRight   45

String cmd = "";                        // the Command 
float arg[3] = {0,0,0};                  // you can pass up to 3 arguments in a command
int ArgIndex;                           // index into arguments
String inputString = "";                // a string to hold incoming data

const float pi = 3.14159;
const float radToDeg = 57.2958;

byte rc_active = 33;         //Signal from BX-24 indicating R/C Control when high
byte busy;
byte LidarMonitor_pin = 8;
byte LidarTrigger_pin = 9;
byte LidarPwrEn_pin = 10;
byte go;

float lidarDist;
int Gamma[3] = {0, 30, 45}; 
float D1;
float D2;
float y1;
float y2;
float angle;
float alpha;
float beta;
float theta;

void setup() {
  delay(500);
  Serial.begin(9600);       //Monitor  
  SetPinModes();  
  go = 0;
  
  digitalWrite(LidarPwrEn_pin, HIGH);  
  LidarServo.write(faceForward);  
}  

void loop() {
  if (go == 1) {
    angle = 129 - (42./90.)*Gamma[1];
    alpha = (129 - angle)*(90./42.)/radToDeg;
    LidarServo.write(angle);
    delay(100);
    D1 =  Lidar();
    Serial.print(D1);
    Serial.write(9);
    
    angle = 129 - (42./90.)*Gamma[2];
    beta = (129 - angle)*(90./42.)/radToDeg;    
    LidarServo.write(angle);
    delay(100);
    D2 =  Lidar();  
    Serial.println(D2);
    LidarServo.write(faceForward);    
    Compute();
    go = 0;
  }
}

//---------------------------------------------------
float Lidar() {
float sum;
float dist;
  
  digitalWrite(9, LOW);             //turn on lidar triggering
  sum = 0;
   for (int i = 0; i < 100; i++) {
    dist = pulseIn(8, HIGH)/10;
    sum += dist;
   }
   digitalWrite(9, HIGH);
   dist = sum/100;
   return dist;
 }
