
void IMU() {
// Get a new sensor event
  sensors_event_t event;
  bno.getEvent(&event);

  // Display the floating point data
  Serial.print("X: ");
  Serial.println(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
  Serial.println("");

  delay(100);  
}
