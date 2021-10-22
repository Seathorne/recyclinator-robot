void ReportEncoder(){
  Serial.println("Encoder: "+String(Counter));
}

void ReportLimits(){
  Serial.println("Top: " + String(TopLimit) + "  Bottom: " + String(BottomLimit));
}
