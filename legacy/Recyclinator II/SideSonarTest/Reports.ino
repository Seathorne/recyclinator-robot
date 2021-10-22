
//----------------------------------------
void Print() {
Serial1.print(rangeLtF,0);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
Serial1.write(9);  
Serial1.print(rangeLtR,0);
Serial1.write(9);
Serial1.print(rangeRtF,0);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
Serial1.write(9);
Serial1.println(rangeRtR,0);
} 


void PrintMon() { 
Serial.print(rangeLtF,1);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
Serial.write(9);
Serial.print(rangeLtR,1);
Serial.write(9);
Serial.print(rangeRtF,1);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
Serial.write(9);
Serial.print(rangeRtR,1); 
Serial.write(9);
Serial.print(rangeLtHall,1);
Serial.write(9);
Serial.println(rangeRtHall, 1);
}
