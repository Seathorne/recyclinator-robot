
void Print() {

Serial1.print((millis() - timeTemp)/1000.0);
Serial1.write(9);
Serial1.print(caseNum);
Serial1.write(9);
Serial1.print(hallCase);
Serial1.write(9);

Serial1.print(rangeLtF,0);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
Serial1.write(9);
Serial1.print(rangeLtR,0);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
Serial1.write(9);
Serial1.print(rangeLtHall,0);
Serial1.write(9);
Serial1.print(rangeRtF,0);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
Serial1.write(9);
Serial1.print(rangeRtR,0);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
Serial1.write(9);
Serial1.print(rangeRtHall,0);
Serial1.write(9);

Serial1.print(wallAng); 
Serial1.write(9);
Serial1.print(featureDepth);
Serial1.write(9);
Serial1.print(hallWidth);
Serial1.write(9);
Serial1.print(encoderLt);
Serial1.write(9);
Serial1.println(encoderRt); 
}

//---------------------------------------------
//---------------------------------------------
void PrintMon() {

Serial.print((millis() - timeTemp)/1000.0);
Serial.write(9);
//Serial.print(caseNum);
//Serial.write(9);
/*
Serial.print(hallCase);
Serial.write(9);

Serial.print(rangeLtF,0);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
Serial.write(9);
Serial.print(rangeRtF,0);
Serial.write(9);
Serial.print(rangeLtHall);
Serial.write(9);
Serial.print(rangeRtHall);
Serial.write(9);
Serial.println(endHallWidth);

Serial.print(wallAng);
Serial.write(9);
Serial.print(LtMtrSpd);
Serial.write(9);
Serial.print(RtMtrSpd);
Serial.write(9);

Serial.print(hallWidth);
Serial.write(9);
Serial.print(featureDepth);
Serial.write(9);
*/
Serial.print(encoderLt);
Serial.write(9);
Serial.println(encoderRt); 
}

