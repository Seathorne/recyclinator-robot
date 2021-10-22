
#include <math.h>
#include <Servo.h>
Servo LidarServo;               //Left write(129);  Forward write(87);  Right write(45)

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
byte num;
byte N;
byte go;

float alpha;
float beta;
float angle;
float lidarDist;
float D1;
float D2;
float theta;
float y;
float distance[15];
float DOne[15];
float DTwo[15];
float gamma[15];
float angAlpha[15];
float angBeta[15];
float m;
float b;
float Y[15];
float Theta[15];
float avgY;
float avgTheta;
float YStdev;
float ThetaStdev;
float YBar;
float ThetaBar;

void setup() {
  delay(500);
  Serial.begin(9600);       //Monitor  
  SetPinModes();  
  m = 166.0/180.0;
  b = 8.0;
  go = 0;
  angle = m*90 + b;  
  digitalWrite(LidarPwrEn_pin, HIGH);     //face forward; 90 deg
  LidarServo.write(angle);  
}  

void loop() {
  if (go == 1) {
    angle = m*alpha + b;
    LidarServo.write(angle);
    delay(100);               // wait for servo to settle    
    D1 =  Lidar();
    
    for (int i = 1; i < num; i++)  {
      beta = alpha - 5;
      angle = m*beta + b;;    
      LidarServo.write(angle);
      delay(100);
      D2 =  Lidar(); 
      Compute();
      distance[i] = y;
      gamma[i] = theta;
      DOne[i] = D1;
      DTwo[i+1] = D2;
      angAlpha[i] = alpha;
      angBeta[i+1] = beta;
      alpha = beta; 
      D1 = D2;
    }

    for (int i = 1; i < num; i++)  {
      Serial.print(distance[i],0);
      Serial.write(9);
      Serial.print(gamma[i]*radToDeg,0);
      Serial.write(9);
    }
    Serial.println( " ");
    angle = m*90 + b;  
    LidarServo.write(angle); 
   Pairs();
   AvgStdDev();
   Filter();
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
