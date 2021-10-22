

#include <math.h>
#include <Servo.h>
Servo LidarServo;               //Left write(129);  Forward write(87);  Right write(45)

String cmd = "";                        // the Command 
float arg[3] = {0,0,0};                  // you can pass up to 3 arguments in a command
int ArgIndex;                           // index into arguments
String inputString = "";                // a string to hold incoming data

const float pi = 3.14159;
const float radToDeg = 57.2958;

byte LidarMonitor_pin = 8;
byte LidarTrigger_pin = 9;
byte LidarPwrEn_pin = 10;
int num;
int N;
byte go;

int numII;
int II[15];
int JJ[15];
int numJJ;

int alpha;
int beta;
float angleFwd;
float angle[15];
float D[15];
float theta;
float y;
float distance[15];
float m;
float b;
float Y[15];
float Theta[15];
float D1;
float D2;

void setup() {
  delay(500);
  Serial.begin(9600);       //Monitor  
  Serial1.begin(57600);
  SetPinModes();  
  m = 166.0/180.0;
  b = 8.0;
  go = 0;
  angleFwd = m*90 + b;  
  digitalWrite(LidarPwrEn_pin, HIGH);     //face forward; 90 deg
  LidarServo.write(angleFwd);  
}  

void loop() {
  if (go == 1) {
    Serial.println("  (Lidar distance, angle):  ");

    Serial1.println("  (Lidar distance, angle):  ");
//  obtain the lidar distances for a set of azimuth angles    
    for (int i = 1; i < (num+1); i++)  {
      angle[i] = m*alpha + b;      //alpha is the initial input angle
      LidarServo.write(angle[i]);
      delay(100);
      D[i] =  Lidar(); 
      alpha -= 5;                  // decrement by 5 degrees
    }
// Print the (distance, angle) pairs      
    for (int i = 1; i <= num; i++)  {
      Serial.write(9);
      Serial.print("(");
      Serial.print(D[i],0);
      Serial.print(", ");
      Serial.print(angle[i]);    
      Serial.println(")");

      Serial1.write(9);
      Serial1.print("(");
      Serial1.print(D[i],0);
      Serial1.print(", ");
      Serial1.print(angle[i]);        
      Serial1.println(")");
    }

    Serial.println("   ");    
    Serial1.println("  ");
// discard (distance, angle) pairs that have discordant adjacent distance values
    FilterDistances();   
    FilterGaps();    
    Pairs();      
    Average();
                  
   Serial.println("  ");
   Serial1.println("  ");

  LidarServo.write(angleFwd);     
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
